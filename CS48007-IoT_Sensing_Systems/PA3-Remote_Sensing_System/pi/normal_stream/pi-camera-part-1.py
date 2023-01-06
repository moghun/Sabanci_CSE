#!/usr/bin/python3

# Capture a JPEG while still running in the preview mode. When you
# capture to a file, the return value is the metadata for that image.

from picamera2 import Picamera2, Preview
import requests
import time
import json

file = open("config.json")
config = json.load(file)
ip = config['ip_address']
port = config['port_number']
file.close()

picam2 = Picamera2()

preview_config = picam2.create_preview_configuration(main={"size": (800, 600)})
picam2.configure(preview_config)

#picam2.start_preview(Preview.QTGL)

picam2.start()
time.sleep(2)


while True:
	metadata = picam2.capture_file("test.jpg")
	time.sleep(0.2)
	try:
		print(requests.post("http://"+ip+":"+str(port)+"/get_people", files={'image': open('test.jpg', 'rb')}))
	except Exception as err:
		print("error", err)
picam2.close()
