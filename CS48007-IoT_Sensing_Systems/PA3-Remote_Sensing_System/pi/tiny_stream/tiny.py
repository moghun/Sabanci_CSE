import cv2
import matplotlib.image as mpimg
import time
from PIL import Image
from picamera2 import Picamera2, Preview
import requests

import json

file = open("config.json")
config = json.load(file)
ip = config['ip_address']
port = config['port_number']
file.close()


# Opencv DNN
net = cv2.dnn.readNet("dnn_model/yolov4-tiny.weights", "dnn_model/yolov4-tiny.cfg")
model = cv2.dnn_DetectionModel(net)
model.setInputParams(size=(320, 320), scale=1/255)

#Get object types
object_types = []
with open("dnn_model/classes.txt", "r") as file_object:
    for obj_type in file_object.readlines():
        object_types.append(obj_type.strip())


#Setup the camera
picam2 = Picamera2()
preview_config = picam2.create_preview_configuration(main={"size": (800, 600)})
picam2.configure(preview_config)
picam2.start_preview(Preview.QTGL)
picam2.start()
time.sleep(2)

#Detect and post the detected
while True:
    metadata = picam2.capture_file("frame.jpg")
    time.sleep(0.2)
    frame = cv2.imread('frame.jpg')
    (obj_id, scr, bx) = model.detect(frame, confThreshold=0.3, nmsThreshold=.4)

    number_of_person=0
    detected_object_dict = {}
    i = 0
    for class_id, score, bounds in zip(obj_id, scr, bx):

        (x, y, w, h) = bounds
        cv2.rectangle(frame, (x, y), (x + w, y + h), (200,0,50), 3)
        curr_obj = object_types[class_id]
        detected_object_dict[i] = {"object_type": curr_obj, "bounding_box":bounds.tolist()}

        if(curr_obj == "person"):
            number_of_person+=1
        cv2.putText(frame, curr_obj, (x, y - 10), cv2.FONT_HERSHEY_PLAIN, 3, (200,0,50), 2)
        i += 1
    print("Number of detected person: ", number_of_person)
    im = Image.fromarray(frame)
    im.save("latest_frame.jpg")
    try:
        print( requests.post("http://"+ip+":"+str(port)+"/tiny_stream", json={'detected_objects': detected_object_dict, "number_of_person": number_of_person}))
    except Exception as err:
        print("error", err)

picam2.close()



