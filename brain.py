#!/usr/bin/python

import serial, os, sys
import time

from smbus import SMBus

sensor_data = {
        "temperature": 0.0,
        "humidity": 0.0
}

def getTnH():
    bus = SMBus(1)
    bus.write_byte(0x40, 0xF5)

    time.sleep(0.3)

    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    humidity = ((data0 * 256 + data1) * 125 / 65536.0) - 6
    time.sleep(0.3)

    bus.write_byte(0x40, 0xE0)
    time.sleep(0.3)

    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    cTemp = ((data0 * 256 + data1) * 175.72 / 65536.0) - 46.85
    fTemp = cTemp * 1.8 + 32

    sensor_data["humidity"] = humidity
    sensor_data["temperature"] = fTemp
try:
    ser1 = serial.Serial('/dev/ttyACM0', 9600, timeout=0.1)
    ser2 = serial.Serial('/dev/ttyACM1', 9600, timeout=0.1)
except serial.serialutil.SerialException:
    print("devices not plugged in")
    sys.exit()
while (True):
    os.system('clear')
    print("Temperature: {} %RH: {}".format(sensor_data["temperature"], sensor_data["humidity"]))
    getTnH()
