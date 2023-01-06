from flask_cors import CORS
from flask import Flask, render_template, request, send_from_directory, send_file, redirect, url_for
import torch 
import numpy as np
from PIL import Image
import matplotlib.image as mpimg
from matplotlib import pyplot as plt
import os.path
import json
from pprint import pprint
import io
import base64

app = Flask(__name__)
CORS(app)

number_of_people = 0
number_of_people_tiny = 0
image = []

@app.route('/')
def home():
  print("homepage")
  return "Hello from server..."

@app.route('/get_people', methods=['POST'], strict_slashes=False)
def postPeople():
    file = request.files['image']
    data = Image.open(file.stream)

    result = model(data)
    result.render()

    global image
    image = result

    predictions = result.pred[0]

    res = result.ims[0]
    buffered = io.BytesIO()
    im_base64 = Image.fromarray(res)
    im_base64.save(buffered, format="JPEG")
    image = base64.b64encode(buffered.getvalue()).decode('utf-8')
    # print(base64.b64encode(buffered.getvalue()).decode('utf-8'))

    personCounter = 0
    predictionKeys = []

    for i in range(len(predictions)):
      arraySize = len(predictions[i]) - 1
      predictionKeys.append(predictions[i][arraySize])
    
    for i in range(len(predictionKeys)):
      if predictionKeys[i] == 0:
        personCounter += 1
    
    print("There are", personCounter, "person(s).")
    global number_of_people 
    number_of_people = personCounter
    return redirect(url_for("getPeople", numberOfPeople=personCounter))


@app.route('/get_people', methods=['GET'], strict_slashes=False)
def getPeople():
    global number_of_people
    return render_template("people.html", numberOfPeople=number_of_people)

@app.route('/video_stream', methods=['GET'], strict_slashes=False)
def get_stream():
  global image
  return render_template("index.html", image=image)


@app.route('/tiny_stream', methods=['POST'], strict_slashes=False)
def tiny_post():
    print(request.json)
    res = request.json
    pprint(res)
    number_of_person = res['number_of_person']
    detected_objects = res['detected_objects']

    global number_of_people_tiny
    number_of_people_tiny = number_of_person

    print("-------INCOMING FRAME---------\n")
    print("(TinyYOLO) There are", number_of_person, "person(s).\n")
    print("All detected objects:")
    for key, value in detected_objects.items():
      print(int(key)+1, "Object type:" ,"\"", value["object_type"] , "\"", "Bounding box:", value["bounding_box"])
    print("--------FRAME END--------")
    return redirect(url_for("tiny_get", numberOfPeople=number_of_person))

@app.route('/tiny_stream', methods=['GET'], strict_slashes=False)
def tiny_get():
    global number_of_people_tiny
    return render_template("tiny.html", numberOfPeople=number_of_people_tiny)




if __name__ == '__main__':
    model = torch.hub.load('ultralytics/yolov5', 'yolov5s', pretrained=True)

    app.run(debug=True , host="0.0.0.0", port="80")

