#!/usr/bin/python

import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
while (True):
    ser.write('1')
    time.sleep(1)
    ser.write('0')
    time.sleep(1)
    print(1)
    print(ser.readline())
    print(0)

