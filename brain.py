#!/usr/bin/python

import serial, os, sys
import time
import keyboard

from smbus import SMBus

sensor_data = {
        "temperature": None,
        "humidity": None,
        "moisture": None,
        "light": None,
        "relay": None
}
blink = True
power = False
ser1 = None
ser2 = None
def toggle():
    global power
    power = not power
keyboard.add_hotkey('p', toggle)

def print_data():
    os.system('clear')
    print("Temperature: {} %RH: {}".format(sensor_data["temperature"], sensor_data["humidity"]))
    if sensor_data["moisture"] is not None:
        print("Moisture level: {}".format(sensor_data["moisture"]))
    else:
        print("No Plant Monitor found!")
    if sensor_data["light"] is not None:
        print("Light level: {} Relay is: {}".format(sensor_data["light"], sensor_data["relay"]))
    else:
        print("No Outlet Guard found!")

    global blink
    if blink:
        print('-')
    else:
        print('|')
    blink = not blink



def getTnH():
    bus = SMBus(1)
    bus.write_byte(0x40, 0xF5)

    time.sleep(0.1)

    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    humidity = ((data0 * 256 + data1) * 125 / 65536.0) - 6
    time.sleep(0.1)

    bus.write_byte(0x40, 0xE0)
    time.sleep(0.1)

    data0 = bus.read_byte(0x40)
    data1 = bus.read_byte(0x40)

    cTemp = ((data0 * 256 + data1) * 175.72 / 65536.0) - 46.85
    fTemp = cTemp * 1.8 + 32

    sensor_data["humidity"] = humidity
    sensor_data["temperature"] = fTemp

def clear_data():
    for key in sensor_data:
        sensor_data[key] = None

def read_from_ser(ser):
    if ser is not None:
        try:
            ser.readline()
            time.sleep(0.1)
            data = ser.readline()
        except serial.serialutil.SerialException:
            clear_data()
            return
        if len(data) == 0:
            return
        if data[0] == '0':
            # Read from Plant Monitor
            try:
                sensor_data["moisture"] = int(data[1])
            except:
                pass
        elif data[0] == '1':
            # Read from Outlet Guard
            try:
                sensor_data["light"] = int(data[1])
                sensor_data["relay"] = int(data[2])
                ser.write(str(int(power)))
            except:
                pass
        ser.flushInput()

while (True):
    if ser1 is None:
        try:
            ser1 = serial.Serial('/dev/ttyACM0', 9600, timeout=0.1)
        except serial.serialutil.SerialException:
            pass
    if ser2  is None:
        try:
            ser2 = serial.Serial('/dev/ttyACM1', 9600, timeout=0.1)
        except serial.serialutil.SerialException:
            pass

    read_from_ser(ser1)
    read_from_ser(ser2)
    getTnH()
    print_data()
    time.sleep(0.5)
    clear_data()


