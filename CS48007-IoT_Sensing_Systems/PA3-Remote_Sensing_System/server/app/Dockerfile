FROM python:3.8

# Create app directory
WORKDIR /

# Install app dependencies
COPY requirements.txt ./

RUN /usr/local/bin/python -m pip install --upgrade pip
RUN pip install --upgrade setuptools
RUN pip install -r requirements.txt
RUN apt-get update
RUN apt-get install ffmpeg libsm6 libxext6  -y

# Bundle app source
COPY . .

EXPOSE 80
CMD [ "python3", "./views.py"]