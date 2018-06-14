# Marie Huynh
# Gemma M0 
# Fades to random colors

import board
import time
import adafruit_dotstar as dotstar
from random import randint

# One pixel connected internally!
dot = dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1, brightness=0.5)

######################### HELPERS ##############################

def fade(color1, color2, steps):
    # start at color1
    red, green, blue = color1

    # calculate step increment for each color component 
    redstep   = (color2[0] - color1[0]) / steps
    greenstep = (color2[1] - color1[1]) / steps
    bluestep  = (color2[2] - color1[2]) / steps

    # move toward color2
    for i in range(steps):
        # not too fast
        time.sleep(.05)
        
        # calculate next step's color
        red = red + redstep
        green = green + greenstep
        blue = blue + bluestep
        dot[0] = [int(red), int(green), int(blue)]
        
        # update LED
        dot.show()

######################### MAIN LOOP ##############################

# start at a pretty blue-green
dot[0] = [0, 200, 200]

while True:
    # choose random new color
    newcolor = [randint(0, 255), randint(0, 255), randint(0, 255)]
    
    # fade to new color
    fade(dot[0], newcolor,40)
