<h1 align="center">SMART SURVEILLANCE CAMERA</h1>

## TABLE OF CONTENTS:

**1. INTRODUCTION**

**2. HARDWARES USED**

**3. SOFTWARES USED**

**4. PROGRAMMING LANGUAGES**

**5. WORKFLOW**     

**6. ROADBLOCKS**   

> - **SETTING UP ARDUCAM WITH WizFi360 BOARD**
> - **SETTING UP YOLOV5**
> - **TELEGRAM API CONNECTION**


**7. OUTPUT**

**8. CONCLUSION**

#

## **1. INTRODUCTION:**

The Smarter Surveillance System project aims to create a smart surveillance camera using the WizFi360 board, Arducam Mini 2MP Plus, and a PIR sensor. The system is designed to detect motion using the PIR sensor and capture an image of the person using the Arducam camera. The captured image is then sent to a Flask server, which is running in the background, to be processed using YOLOv5, an object detection algorithm. The first step in building a smarter surveillance system is to gather the necessary hardware components. For this project, we will be using the WizFi360 board, Arducam Mini 2MP Plus, and a PIR (Passive Infrared) sensor. These components will work together to detect motion, capture an image, and send it to a Flask server for processing. The WizFi360 board is a powerful IoT module that provides WiFi connectivity and supports various wireless protocols such as TCP/IP, HTTP, FTP, and SSL/TLS. It has an onboard processor and can be easily programmed using the Arduino IDE, making it an ideal choice for IoT applications. 

The Arducam Mini 2MP Plus is a small camera module with a resolution of 2 megapixels. It supports various interfaces, including SPI, I2C, and UART, and can be easily connected to the WizFi360 board. The PIR sensor is a motion detection sensor that detects changes in infrared radiation emitted by a moving object. It is commonly used in security systems and can detect motion up to several meters away. If a person is detected in the captured image, the system sends a notification to a Telegram channel, indicating that someone is in a restricted area. The notification includes the detected picture, allowing for quick response and action. Overall, the Smarter Surveillance System is an innovative and efficient way to monitor and secure restricted areas, making use of the latest technology available.

#

## **2. HARDWARES USED:**

- [WizFi360-EVB-Pico](https://www.hackster.io/wiznet/products/wizfi360-evb-pico3)
- [JUMPER WIRES](https://www.hackster.io/diyables/products/jumper-wires)
- [ARDUCAM MINI 2MP PLUS](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
- [PIR SENSOR](https://www.hackster.io/sb-components-ltd/products/pir-infrared-motion-sensor)

#

## **3. SOFTWARE AND SERVICES USED:**

- [openCV](https://opencv.org/)
- [AURDINO IDE](https://www.arduino.cc/)
- [FLASK-ASK](https://github.com/johnwheeler/flask-ask)

#

## **4. PROGRAMMING LANGUAGES**
- [C++](https://isocpp.org/)
- [PYTHON](https://www.python.org/)

#

## **4. WORK FLOW:**

- Setup the Hardware Components

The first step is to set up the hardware components. Connect the Arducam Mini 2MP Plus camera module to the WizFi360 board using the SPI interface. Connect the PIR sensor to one of the digital pins of the WizFi360 board. Connect the power source to the WizFi360 board.

- Configure the WizFi360 Board

Configure the WizFi360 board to connect to the WiFi network. Program the board using the Arduino IDE to communicate with the Arducam camera module and PIR sensor. Set up the board to capture an image when the PIR sensor detects motion.

- Capture an Image

When the PIR sensor detects motion, the WizFi360 board triggers the Arducam camera module to capture an image. The captured image is saved in the memory of the WizFi360 board.

- Send the Image to Flask Server

The WizFi360 board is programmed to send the captured image to a Flask server using an HTTP POST request. The Flask server is running in the background and is waiting to receive the image.

- Process the Image Using YOLOv5

Once the Flask server receives the image, it processes the image using the YOLOv5 algorithm. YOLOv5 is an object detection algorithm that can detect objects in real-time with high accuracy. The Flask server is programmed to run the YOLOv5 algorithm on the captured image to detect whether there is a person in the image.

- Send a Notification to Telegram

If a person is detected in the image, the Flask server generates a notification and sends it to a Telegram channel. The notification includes a message indicating that someone is in a restricted area, along with the detected image.

- Take Action

Once a notification is received on the Telegram channel, appropriate action can be taken, such as alerting security personnel or sounding an alarm.


## **4. ROADBLOCKS:**

**1. SETTING UP ARDUCAM WITH WizFi360 BOARD**

Below shows the overall setup for the WizFi360 with the Arducam. The pin configuration is also given below:

<p align="center">
  <img src="https://user-images.githubusercontent.com/114398468/226533314-84c55a13-6cd5-4c4a-9656-a9510d5c1b19.jpg" width="50%" />
</p>


The WizFi360 is a compact and powerful Wi-Fi module that provides seamless connectivity to the Internet of Things (IoT) devices. It features a low-power ARM Cortex-M4 microcontroller and a high-performance Wi-Fi transceiver that supports IEEE 802.11 b/g/n protocols. With its built-in security features and easy-to-use software development kit, the WizFi360 is an ideal solution for creating smart and connected IoT applications.On the other hand, a PIR (Passive Infrared) sensor is a type of motion sensor that detects movement by sensing changes in infrared radiation levels. It is commonly used in security systems, automatic lighting, and other applications where motion detection is required. PIR sensors are called "passive" because they do not emit any energy themselves; instead, they detect the energy emitted by other objects, such as the human body.

When combined, the WizFi360 and PIR sensor can create powerful and intelligent IoT applications that enable remote monitoring and control of motion detection systems. For example, a PIR sensor can detect movement in a room and send a signal to the WizFi360 module, which can then send a notification to a smartphone app or trigger an alarm. The WizFi360 can also be used to control the sensitivity and operating modes of the PIR sensor, making it a flexible and customizable solution for a wide range of IoT applications.


<p align="center">
  <img src="https://github.com/Stebin-17/Intelligent-Door-Access-System-with-Facial-Recognition-and-Voice-Control/blob/main/Door-Facial-System/Files/AruduCam-Mini-2MP-Plus-SPI-Camera-Module-Pin.jpg" width="75%" />
</p>

The ArduCam provides document and source codes [SPI Camera for Raspberry Pi Pico](https://www.arducam.com/docs/pico/arducam-camera-module-for-raspberry-pi-pico/spi-camera-for-raspberry-pi-pico) and it also uses SPI0. To avoid the confliction, this project uses SPI1 for the ArduCam OV2640 Module.ArduCam OV2640 Module requires CS, MOSI, MISO, SCLK pins for SPI connection, and SDA, SCL pins for I2C connection. This project modified the source code of ArduCam to use SPI1.

**Pico pin configuration for ArduCam OV2640**

```
1. CS   --> GPIO 13
2. MOSI --> GPIO 11
3. MISO --> GPIO 12
4. SCLK --> GPIO 10
5. SDA  --> GPIO 8
6. SCL  --> GPIO 9
```

<h2>Code Explaination</h2>

> WizFi_Flask Server/WizFi_CamPost.ino

- ```setup()```:
This function is called once when the Arduino board is powered on or reset. It initializes the serial communication with a baud rate of 115200 and also initializes the ArduCAM module by calling the ArduCam_setup() function.

- ```loop()```:
This function is called repeatedly after the setup() function. It captures an image with the ArduCAM module, sends the image data to a server using the Wi-Fi module, and then waits for a period of time before repeating the process.

- ```ArduCam_setup()```:
This function initializes the ArduCAM module by setting the CS pin as an output and initializing the Wire library for I2C communication.

- ```ArduCam_sendImg()```:
This function captures an image with the ArduCAM module and stores the image data in the img_buf array. It then calls the http_postData() function to send the image data to the server.

- ```http_postData(byte *buf, uint32_t length)```:
This function sends the image data to a server using the Wi-Fi module. It first checks if the client is connected to the server, and if not, it tries to reconnect several times before giving up. It then sends an HTTP POST request to the server with the image data as the payload. The payload includes the file name and content type of the image. Finally, it waits for a response from the server before closing the connection.

- ```buffer_transfer(byte *bptr, size_t len)```:
This function sends a buffer of data to the server in multiple chunks of size max_transfer (1024 bytes in this code) to prevent buffer overflows.

- ```client```:
This object of the WiFiClient class is used to establish a connection with the server and send/receive data.








