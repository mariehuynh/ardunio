# Marie Huynh
# External NeoPixel with Brightness Control
# Runs on Circuit Playground Express + 24 NeoPixel ring + potentiometer

# Note: Gemma M0 uses D1 but Circuit Playground Express uses A1 for NeoPixels

import time
import board
import analogio
from neopixel import NeoPixel

pixel_pin = board.A1
pot_pin = analogio.AnalogIn(board.A5)
num_pixels = 24

pixels = NeoPixel(pixel_pin, num_pixels, brightness=.1, auto_write=False)

def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 0 or pos > 255:
        return (0, 0, 0)
    if pos < 85:
        return (255 - pos * 3, pos * 3, 0)
    if pos < 170:
        pos -= 85
        return (0, 255 - pos * 3, pos * 3)
    pos -= 170
    return (pos * 3, 0, 255 - pos * 3)

def rainbow_cycle(wait, speed):
    for j in range(255):
        for i in range(num_pixels):
            rc_index = (i * 256 // num_pixels) + (j * speed)
            pixels[i] = wheel(rc_index & 255)
        pixels.show()
        time.sleep(wait)
        adjust_brightness() # much better response time here than in main loop

def adjust_brightness():
    pixels.brightness = pot_pin.value/65536
    # print((pixels.brightness,)) # print for plotter
    
while True:
    rainbow_cycle(0, 10)
