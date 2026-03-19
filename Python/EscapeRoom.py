import serial, time
from playsound import playsound

def connect(index):
    started = False
    # print("Connecting to Arduino port " + str(ports[index]))
    print("Connecting to module", index+1)
    while not started:
        try:
            arduino = serial.Serial(port=ports[index], baudrate=rates[index], timeout=.1)
            modules.append(arduino)
            started = True
            # print("Connected to port " + str(ports[index]))
            print("Connected to module", index+1)
        except:
            # print("Nope")
            pass
def send(index, x):
    print("Sending")
    modules[index].write(bytes(str(x), 'utf-8'))
def read(index):
    global listen
    global ending
    while modules[index].in_waiting > 0:
        try:
            data = int(modules[index].readline())
            # data = modules[index].readline()
            print("Module ", index+1, ": ", data, sep="")
            if data == 1:
                listen = False
            elif data == 2:
                listen = False
                ending = 1
            elif data == 3:
                listen = False
                ending = 2
        except:
            pass

ports = ['COM9', 'COM8', 'COM6']
rates = [9600, 31250, 57600]
modules = []
listen = False
ending = 0

print("Connecting to modules...")
for i in range(3):
    connect(i)
    time.sleep(0.05)
print("Successfully connected to modules!\n")

# while True:
#     read(0)
#     read(1)
#     read(2)

print("Playing initial audio")
# time.sleep(5)
playsound("intro.mp3")
print("Starting module 1")
send(0, 1)
print("Started module 1")
listen = True
while listen:
    read(0)
print("Module 1 finished!")



print("Playing audio")
# time.sleep(5)
playsound("mod1.mp3")
print("Starting module 2")
send(1, 1)
print("Started module 2")
listen = True
while listen:
    read(1)
print("Module 2 finished!")



print("Playing audio")
# time.sleep(2)
playsound("mod2.mp3")
print("Starting module 3")
send(2, 1)
print("Started module 3")
listen = True
while listen:
    read(2)
print("Module 3 finished!")



print("Playing audio")
playsound("mod3.mp3")
print("Finished playing audio")
listen = True
while listen:
    read(2)
if ending == 1:
    print("Did nothing, playing audio for ending 1")
    playsound("released.mp3")
elif ending == 2:
    print("Pressed button, playing audio for ending 2")
    playsound("destroyed.mp3")