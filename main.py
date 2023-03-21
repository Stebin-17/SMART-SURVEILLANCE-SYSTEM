import os
import cv2
from flask import Flask, request, redirect, flash, url_for, render_template
from flask_wtf import FlaskForm
from wtforms import FileField
from flask_uploads import configure_uploads, IMAGES, UploadSet
import telegram
import os
import requests
import subprocess
import time
import asyncio
import threading


from yolov5.detect import run

app = Flask(__name__)

photos = UploadSet("photos", IMAGES)
app.config["UPLOADED_PHOTOS_DEST"] = "static/img"
app.config["SECRET_KEY"] = os.urandom(24)
configure_uploads(app, photos)
count = 1

# Initialize your bot
bot = telegram.Bot(token='5881496177:AAFkxzUugfC0qVOPU55jeDQhiVj_ea8LGbA')
chat_id= "778996496"

flag = False

def send_telegram_message(message,image_path):
    try:
        bot.send_message(chat_id=chat_id, text=message)
        bot.send_photo(chat_id=chat_id, photo=open(image_path, 'rb'))
    except Exception as e:
        print("An exception occurred while sending the telegram message:", str(e))

def detect_person():
    global flag
    print(flag)

    if flag == True:
        try:
            detect = run('/home/christ-infotech-007/Rohan/survillience_motion_camera/yolov5/yolov5s.pt', '/home/christ-infotech-007/Rohan/survillience_motion_camera/FlaskServer/static/img/capture01.jpeg',classes=0)
            image_file_name ='/home/christ-infotech-007/Rohan/survillience_motion_camera/yolov5/runs/detect/exp/capture01.jpeg'

            print(detect)

            for i in detect:
                if "person" in i:
                    print("Hello")
                    message = "Somebody entered at the door"
                    send_telegram_message(message, image_file_name)
                    break
                else:
                    print("No person found")
        except Exception as e:
            print("An exception occurred while detecting the person:", str(e))
            flag = False
        flag = False


@app.route("/", methods=['GET', 'POST'])
def upload():
    global count
    global flag
    if request.method == 'POST' and 'image/jpeg' == request.content_type:
        filepath = "static/img/capture%02d.jpeg" % count
        f = open(filepath, "wb")
        #count = count + 1
        f.write(bytes(request.data))
        f.close()
        print(filepath)

        flag  = True
        process = threading.Thread(target=detect_person, args=())
        process.start()
        #return render_template('show_image.html', user_image=filepath)
        return f'{filepath}'
    # print("in the yolo")
    # detect_person()

    return render_template('upload.html')

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=1077)
