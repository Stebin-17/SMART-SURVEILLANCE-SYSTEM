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




