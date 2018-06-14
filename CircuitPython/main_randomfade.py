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
dot = dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1, brightness=0.5)

######################### HELPERS ##############################

def fade(color1, color2, steps):

    red, green, blue = color1

    # calculate step increment for each color component 
    redupdate = (color2[0] - color1[0]) / steps
    greenupdate = (color2[1] - color1[1]) / steps
    blueupdate = (color2[2] - color1[2]) / steps

    # move toward color2
    for i in range(steps):
        time.sleep(.1)
        red = red + redupdate
        green = green + greenupdate
        blue = blue + blueupdate

        dot[0] = [int(red), int(green), int(blue)]
        dot.show()
        print(str(i) + ":" + str(dot[0]))

######################### MAIN LOOP ##############################

# start at a pretty blue-green
dot[0] = [0, 200, 200]

while True:
    # choose random new color
    newcolor = [randint(0, 255), randint(0, 255), randint(0, 255)]
    
    # fade to new color
    fade(dot[0], newcolor,40)
