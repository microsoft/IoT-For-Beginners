import time
import serial

serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
serial.reset_input_buffer()
serial.flush()

def printGPSData():
    print(line.rstrip())

while True:
    line = serial.readline().decode('utf-8')

    while len(line) > 0:
        printGPSData()
        line = serial.readline().decode('utf-8')

    time.sleep(1)
