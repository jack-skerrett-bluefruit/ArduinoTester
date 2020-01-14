import serial #this is the python library that means we dont have to do anything fancy, we can just cheat
import time #we have to use this because timings can be a bit fucky, we will try and figure this out with a scope?
import someCleverPy

acceptedCommands = ["ledon", "ledoff", "exit"] #a list of commands, pretty eeassssyyy
serialPort = ""
 
while(1):
    var = input("Type \'ls\' to see a list of all available serial ports. If you know the port you want to open, type \'COMX\' where X is the number of the desired port. ")
    print()
    if(var.strip().lower() == "ls"):
        print(someCleverPy.serial_ports())
        print()
    elif(var.strip().lower().startswith("com")):
        serialPort = var.upper()
    else:
        print("Don't be naughty, do it again")


ser = serial.Serial('COM12', 115200) #this is the way we open a serial port, we can manipulate the serial port by manipulating the "ser" object

time.sleep(2) #I added this as a bit of debug because I wasn't getting successful communication, so I added in a delay to make sure everything had enough time to talk to each other. This made it work. Arduinos have a start up time

def doSomething(command): #a function that compares user inputs and then writes to the serial port depending on what the comment is
    if(command == "ledon"):
        ser.write(b'$ledon\r')
        response = str(ser.read(5))   #reading back what happens after you send the command
        print(response.lstrip("b\'").rstrip("\'"))
    if(command == "ledoff"):
        ser.write(b'$ledoff\r')
        response = str(ser.read(6))
        print(response.lstrip("b\'").rstrip("\'"))
    if(command == "exit"):
        exit()

while(1):
    userResponse = input()
    if(userResponse in acceptedCommands):
        doSomething(userResponse)
    else:
        print("That's not a commands. Valid commands include: ", end = "")
        print(*acceptedCommands, sep = ", ")

ser.close()
