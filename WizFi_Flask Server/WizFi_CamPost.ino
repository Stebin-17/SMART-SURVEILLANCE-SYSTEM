/*
  Telnet client

 This sketch connects to a a telnet server (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.  You'll need a telnet server
 to test this with.
 Processing's ChatServer example (part of the network library) works well,
 running on port 10002. It can be found as part of the examples
 in the Processing application, available at
 http://processing.org/

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 14 Sep 2010
 modified 9 Apr 2012
 by Tom Igoe
 */

#include <SPI.h>
#include <Wire.h>
#include <SPI.h>
#include "ArduCAM_OV2640.h"
#include "memorysaver.h"

#include "WizFi360.h"

// setup according to the device you use
#define WIZFI360_EVB_PICO

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
#if defined(ARDUINO_MEGA_2560)
SoftwareSerial Serial1(6, 7); // RX, TX
#elif defined(WIZFI360_EVB_PICO)
SoftwareSerial Serial2(6, 7); // RX, TX
#endif
#endif

/* Baudrate */
#define SERIAL_BAUDRATE   115200
#if defined(ARDUINO_MEGA_2560)
#define SERIAL1_BAUDRATE  115200
#elif defined(WIZFI360_EVB_PICO)
#define SERIAL2_BAUDRATE  115200
#endif

/* Wi-Fi info */
//char ssid[] = "wiznet";       // your network SSID (name)
//char pass[] = "0123456789";   // your network password
char ssid[] = "TP-Link_8780";       // your network SSID (name)
char pass[] = "18122121";   // your network password

int status = WL_IDLE_STATUS;  // the Wifi radio's status

// Initialize the Ethernet client object
WiFiClient client;

// Enter the IP address of the server you're connecting to:
//IPAddress server(192, 168, 0, 121);
//IPAddress myDns(192, 168, 0, 1);
//char server[] = "arduino.tips";
char server[] = "192.168.0.121";
uint16_t port = 1077;

#define max_transfer 1024
#define max_buffer  (20 * max_transfer)

byte img_buf[max_buffer];

int count = 0;
char c = 0;
bool is_capture = false;
unsigned long prevmillis = 0;

void buffer_transfer(byte *bptr, size_t len) {
  size_t sent = 0;
  for (; sent + max_transfer < len; ) {
    client.write(bptr, max_transfer);
    sent += max_transfer;
    bptr += max_transfer;
    //Serial.println(max_transfer);
  }
  client.write(bptr, len - sent);

  Serial.print("Sent: "); Serial.println(len);
}

void http_postData(byte *buf, uint32_t length) {
  count = 0;

  // if the server's disconnected, stop the client
  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();
    delay(100);
  }
 
  // if the server's disconnected, reconnect the client:
  while (!client.connected()) {
    Serial.println();
    Serial.println("disconnected. Reconnecting...");
    if (client.connect(server, port)) {
      Serial.println("connected");
      break;
    } else {
      // if you didn't get a connection to the server:
      if (++count > 5) {  // Retry 5 times.
        Serial.println("HTTP Post failed. Give up.");
        return;
      }      
      Serial.println("connection failed");
      delay(1000);
    }
  }

  //delay(200);

  Serial.println("POST Start [[[[[[[[[[[[[[");

  client.write("POST / HTTP/1.1\n");
  client.write("Host: 192.168.0.121\n");
  client.write("User-Agent: Arduino/1.0\n");
  client.write("Connection: close\n");
  client.write("Content-Disposition: form-data; name=\"photo\"; filename=\"capture.jpeg\"\n");
  client.write("Content-Type: image/jpeg\n");
  client.write("Content-Length: ");
  char lenbuf[20];
  sprintf(lenbuf, "%d\n\n", length);
  client.write(lenbuf);
  buffer_transfer(buf, length);
  client.write("\n\n");
  //client.flush();
  
  Serial.println("POST End ]]]]]]]]]]]]]]]]");

  delay(100);

  /*
  prevmillis = millis();
  while (millis() - prevmillis < 5000) {
      if (client.available()) {
        Serial.println("Response");
        break;
      }
      delay(10);
  }
  
  int len = client.available();
  if (len > 0) {
    byte buffer[200];
    if (len > 200) len = 200;
    client.read(buffer, len);
    Serial.write(buffer, len); // show in the serial monitor (slows some boards)
    Serial.println("");
  }
  //*/
  
  //client.stop();
}

//=========================================================
void ArduCam_setup();
void ArduCam_sendImg();

//const int CS = 5; //GPIO-5 for SPI
const int CS = 13;  //GPIO-13 for SPI1
uint8_t vid, pid;
ArduCAM myCAM( OV2640, CS );

void ArduCam_setup() {
  uint8_t temp;

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  Wire.setSDA(8);
  Wire.setSCL(9);
  // This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL)
  
  // Using SPI
  //SPI.setSCK(2);
  //SPI.setTX(3);
  //SPI.setRX(4);
  //SPI.setCS(CS);
  //myCAM.Arducam_init(&SPI, &Wire);
  
  // Using SPI1
  SPI1.setSCK(10);
  SPI1.setTX(11);
  SPI1.setRX(12);
  SPI1.setCS(CS);
  myCAM.Arducam_init(&SPI1, &Wire);
  
  //Reset the CPLD
  myCAM.write_reg(0x07, 0x80);
  delay(100);
  myCAM.write_reg(0x07, 0x00);
  delay(100);

  while(1){
    //Check if the ArduCAM SPI bus is OK
    myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
    temp = myCAM.read_reg(ARDUCHIP_TEST1);
    if (temp != 0x55){
      Serial.println(temp);
      Serial.println("ACK CMD SPI interface Error! END");
      delay(1000);
      continue;
    }else{
      Serial.println("ACK CMD SPI interface OK. END");
      break;
    }
  }

  while(1){
    //Check if the camera module type is OV2640
    myCAM.wrSensorReg8_8(0xff, 0x01);
    myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
    myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
    if ((vid != 0x26 ) && (( pid != 0x41 ) || ( pid != 0x42 ))){
      Serial.println("ACK CMD Can't find OV2640 module! END");
      delay(1000);continue;
    }
    else{
      Serial.println("ACK CMD OV2640 detected. END");
      break;
    } 
  }

  //Change to JPEG capture mode and initialize the OV2640 module
  myCAM.set_format(JPEG);
  myCAM.InitCAM();
  //myCAM.OV2640_set_JPEG_size(OV2640_176x144);
  myCAM.OV2640_set_JPEG_size(OV2640_320x240);
  //myCAM.OV2640_set_JPEG_size(OV2640_640x480);
  delay(50);
  myCAM.OV2640_set_Light_Mode(Auto);
  delay(50);
  //myCAM.OV2640_set_Color_Saturation(Saturation0);
  myCAM.OV2640_set_Color_Saturation(Saturation0);
  delay(50);
  //myCAM.OV2640_set_Brightness(Brightness0);
  myCAM.OV2640_set_Brightness(Brightness0);
  delay(50);
  //myCAM.OV2640_set_Contrast(Contrast0);
  myCAM.OV2640_set_Contrast(Contrast0);
  delay(50);
  myCAM.OV2640_set_Special_effects(Bluish);
  //myCAM.OV2640_set_Special_effects(Greenish);
  //myCAM.OV2640_set_Special_effects(Reddish);
  //myCAM.OV2640_set_Special_effects(BW);
  //myCAM.OV2640_set_Special_effects(Negative);
  //myCAM.OV2640_set_Special_effects(BWnegative);
  //myCAM.OV2640_set_Special_effects(Antique);
  myCAM.OV2640_set_Special_effects(Normal);
  myCAM.OV2640_set_Light_Mode(Office);
  delay(1000);
  myCAM.clear_fifo_flag();
  delay(50);
}

int ArduCam_capture() {
  uint32_t length = 0;
  uint32_t read_len = 0;
  byte *bptr;
  
  myCAM.flush_fifo();
  myCAM.clear_fifo_flag();
  //Start capture
  myCAM.start_capture();

  Serial.println("Wait CAP_DONE_MASK...");
  while (!myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK))
    delay(1);

  Serial.print("CAM Image Ready.");
  delay(1);
  
  //read_fifo_burst(myCAM);
  length = myCAM.read_fifo_length();
  Serial.println(length);

  myCAM.CS_LOW();
  myCAM.set_fifo_burst();//Set fifo burst mode

  bptr = img_buf;
  
  // Read image from ArduCam
  while (1) {
    if (length > max_transfer) {
      read_len = myCAM.transferBytes((uint8_t*)NULL, (uint8_t*)bptr, (uint32_t)max_transfer);
      //Serial.println(read_len);
      //ethernet_transfer(buf, read_len);
      length -= read_len;
      bptr += read_len;
    } else {
      read_len = myCAM.transferBytes((uint8_t*)NULL, (uint8_t*)bptr, (uint32_t)length);
      //Serial.println(read_len);
      //ethernet_transfer(buf, read_len);
      break;
    }
    //delayMicroseconds(15);
  }

  myCAM.CS_HIGH();
  //Clear the capture done flag
  myCAM.clear_fifo_flag();
  Serial.println("Copied to buffer");

  // Find end of image
  bptr = img_buf+2;
  for (length = 2; length<max_buffer ;++length, ++bptr) {
    if (*bptr == 0xFF) {
      if (*(bptr+1) == 0xD9) {
        Serial.print("End of image. New length = ");
        length += 2;  // Include 0xFF 0xD9
        Serial.println(length);
        break;
      }
    }
  }

  return length;
}

/*/
void ArduCam_sendImg() {
  size_t length = 0;
  
  length = ArduCam_capture();  
  // Sned image to server.
  ethernet_transfer(img_buf, length);
}
/*/
void ArduCam_sendImg() {
  size_t length = 0;
  
  length = ArduCam_capture();  
  // Sned image to server.
  http_postData(img_buf, length);
}
//*/


//=========================================================

void setup() {
  // initialize serial for debugging
  Serial.begin(SERIAL_BAUDRATE);
  // initialize serial for WizFi360 module
#if defined(ARDUINO_MEGA_2560)
  Serial1.begin(SERIAL1_BAUDRATE);
#elif defined(WIZFI360_EVB_PICO)
  Serial2.begin(SERIAL2_BAUDRATE);
#endif
  // initialize WizFi360 module
#if defined(ARDUINO_MEGA_2560)
  WiFi.init(&Serial1);
#elif defined(WIZFI360_EVB_PICO)
  WiFi.init(&Serial2);
#endif

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Initial setup for ArduCam
  ArduCam_setup();
}

void loop() {
  c = 0x96;

  // if the server is ready, send captured image:
  if (c == 0x96)
  {
    c = 0;
    ArduCam_sendImg();
    count++;
    Serial.println(count);

    delay(5000);
  }
}
