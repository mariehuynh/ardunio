# Gemma M0 
# Fades to random colors

import board
import time
from digitalio import DigitalInOut, Direction, Pull
from analogio import AnalogIn, AnalogOut
from touchio import TouchIn
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode
import adafruit_dotstar as dotstar
from random import randint

# One pixel connected internally!
dot = dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1, brightness=1)

# Built in red LED
led = DigitalInOut(board.D13)
led.direction = Direction.OUTPUT

# Analog output on A0
aout = AnalogOut(board.A0)

# Analog input on A1
analog1in = AnalogIn(board.A1)

# Capacitive touch on A2
touch2 = TouchIn(board.A2)

# Used if we do HID output, see below
kbd = Keyboard()

######################### HELPERS ##############################

def fade(color1, color2, steps):

    red, green, blue = color1
    redupdate = (color2[0] - color1[0]) / steps
    greenupdate = (color2[1] - color1[1]) / steps
    blueupdate = (color2[2] - color1[2]) / steps

    for i in range(steps):
        time.sleep(.1)
        red = red + redupdate
        green = green + greenupdate
        blue = blue + blueupdate

        dot[0] = [int(red), int(green), int(blue)]
        dot.show()
        print(str(i) + ":" + str(dot[0]))

######################### MAIN LOOP ##############################

i = 100
j = 100
k = 100
dot[0] = [i, j, k]

while True:
    # choose random new color
    newcolor = [randint(0, 255), randint(0, 255), randint(0, 255)]
    # spin internal LED around!
    #dot[0] = wheel(i)
    fade(dot[0], newcolor,40)
