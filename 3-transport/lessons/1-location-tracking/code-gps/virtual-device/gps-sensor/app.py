from counterfit_connection import CounterFitConnection
CounterFitConnection.init('127.0.0.1', 5000)

import time
import counterfit_shims_serial

serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')

def printGPSData(line):
    print(line.rstrip())

while True:
    line = serial.readline().decode('utf-8')

    while len(line) > 0:
        printGPSData(line)
        line = serial.readline().decode('utf-8')

    time.sleep(1)