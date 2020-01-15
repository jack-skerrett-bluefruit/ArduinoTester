import serial
import time
import someCleverPy


print(someCleverPy.serial_ports())

acceptableCommands = ["ledon", "ledoff", "exit"]
while(1):
    comPort = "COM" + input("Enter the com port number: ")
    try:
        serialConnection = serial.Serial(comPort, 115200)
        break
    except:
        print("Invalid com port.")

time.sleep(2)

while(1):
    command = input("command please: ")
    if(command == "ledon"):
        serialConnection.write(b"$ledon\r")
    elif(command == "ledoff"):
        serialConnection.write(b"$ledoff\r")
    elif(command == "exit"):
        exit(0)
    else:
        print("This is gibberish, try these instead")
        print(acceptableCommands)