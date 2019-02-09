#!/usr/bin/env python
import serial
import signal
import json
import sys
import requests
import subprocess
import time

some_value = 0

def to_node(type, message):
    if type == "tap":
        print("play/pause")
        requests.get("http://localhost:5005/Living%20Room/playpause")
    elif type == "gesture" and message == "left":
        print("next")
        requests.get("http://localhost:5005/Living%20Room/next")
    elif type == "gesture" and message == "right":
        print("previous")
        requests.get("http://localhost:5005/Living%20Room/previous")
    elif type == "rotate" and (message == "clockwise" or message == "anticlockwise"):
        volume = str(round(some_value / 100))
        print("volume: " + volume)
        requests.get("http://localhost:5005/Living%20Room/volume/" + volume)


def flick(start, finish):
    print start
    print finish
    if start == "east" and finish == "west":
        to_node("gesture", "left")
    if (start == "west") and (finish == "east"):
        to_node("gesture", "right")
    if start == "north" and finish == "south":
        to_node("gesture", "down")
    if start == "south" and finish == "north":
        to_node("gesture", "up")


def spinny(delta):
    global some_value
    some_value += delta * 6

    if some_value < 0:
        some_value = 0
    elif some_value > 10000:
        some_value = 10000

    if delta > 0:
        to_node("rotate", "clockwise")
    elif delta < 0:
        to_node("rotate", "anticlockwise")


def tap(position):
     monitor_status = str(subprocess.check_output("DISPLAY=:0 xset q | grep Monitor", shell = True))
     if "On" in monitor_status :
         # to_node("tap", position)
         print("no pause")
     subprocess.call("DISPLAY=:0 xset dpms force on", shell = True)


def handle_data(reading):
    reading = str(reading)

    def RepresentsInt(s):
        try:
            int(s)
            return True
        except ValueError:
            return False

    if reading.startswith("FLICK"):
        print('FLICK')
        flick(reading.split("_")[1].strip(" ").lower(), reading.split("_")[2].rstrip().lower())
    elif reading.startswith("TOUCH"):
        print('touch')
        tap("CENTER")
    elif RepresentsInt(reading.rstrip()):
        print 'AIRWHEEL'
        print reading
        spinny(int(reading))


state = requests.get("http://localhost:5005/Living%20Room/state").json()
new_volume = state["volume"]
some_value = new_volume * 100
print("Volume " + str(new_volume) + " fetched from sonos")
print("Ready for input...")
ser = serial.Serial('/dev/ttyACM0',9600)
while True:
    reading = ser.readline().decode()
    ser.flushInput()
    time.sleep(.005)
    handle_data(reading)

signal.pause()
