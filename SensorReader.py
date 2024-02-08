from serial.tools import list_ports
import serial
import time
import csv

# From "Curio Res" Youtube video
# https://youtu.be/fIlklRIuXoY 

# Note: Serial communications using windows are EXCLUSIVE.
# This means that only one process can read from a serial port at a time. 

# Note: Can run multiple python scripts at the same time using BASH commands and the & operator.

ports = list_ports.comports()
for port in ports: print(port)
# COM3 = Arduino Port

f = open("data.csv","w",newline ='')
f.truncate()

serialCom = serial.Serial('COM3',115200) # opens the serial port connected to the Arduino, communicates at the same baud rate.

serialCom.setDTR(False) # Don't allow serial data communication
time.sleep(1) # Waits for 1 sec
serialCom.flushInput() # Flush the current data points
serialCom.setDTR(True) # Ready for communication

kmax = 5 # Number of data points to read

for k in range(kmax):
    try:
        s_bytes = serialCom.readline() # Read data from the serial port

        decoded_bytes = s_bytes.decode("utf-8").strip('\r\n') # Removes carriage return and line break

        # Line parsing
        if k == 0:
            values = decoded_bytes.split(",")
        else:
            values = [float(x) for x in decoded_bytes.split()]
            values[0] = values[0]/1000 # Convert ms -> s

        print(values)

        # Saving data to csv
        writer = csv.writer(f,delimiter=",")
        writer.writerow(values)

    except: 
        print("ERROR. Line was not recorded")

f.close() # closes the csv file

