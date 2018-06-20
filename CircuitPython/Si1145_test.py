import board
import busio
from adafruit_bus_device.i2c_device import I2CDevice
import time

REGISTERS = (0, 256)  # Range of registers to read, from the first up to (but
                      # not including!) the second value.

REGISTER_SIZE = 2     # Number of bytes to read from each register.
# COMMANDS
SI1145_PARAM_QUERY                      = 0x80
SI1145_PARAM_SET                        = 0xA0
SI1145_NOP                              = 0x0
SI1145_RESET                            = 0x01
SI1145_BUSADDR                          = 0x02
SI1145_PS_FORCE                         = 0x05
SI1145_ALS_FORCE                        = 0x06
SI1145_PSALS_FORCE                      = 0x07
SI1145_PS_PAUSE                         = 0x09
SI1145_ALS_PAUSE                        = 0x0A
SI1145_PSALS_PAUSE                      = 0xB
SI1145_PS_AUTO                          = 0x0D
SI1145_ALS_AUTO                         = 0x0E
SI1145_PSALS_AUTO                       = 0x0F
SI1145_GET_CAL                          = 0x12

# Parameters
SI1145_PARAM_I2CADDR                    = 0x00
SI1145_PARAM_CHLIST                     = 0x01
SI1145_PARAM_CHLIST_ENUV                = 0x80
SI1145_PARAM_CHLIST_ENAUX               = 0x40
SI1145_PARAM_CHLIST_ENALSIR             = 0x20
SI1145_PARAM_CHLIST_ENALSVIS            = 0x10
SI1145_PARAM_CHLIST_ENPS1               = 0x01
SI1145_PARAM_CHLIST_ENPS2               = 0x02
SI1145_PARAM_CHLIST_ENPS3               = 0x04

SI1145_PARAM_PSLED12SEL                 = 0x02
SI1145_PARAM_PSLED12SEL_PS2NONE         = 0x00
SI1145_PARAM_PSLED12SEL_PS2LED1         = 0x10
SI1145_PARAM_PSLED12SEL_PS2LED2         = 0x20
SI1145_PARAM_PSLED12SEL_PS2LED3         = 0x40
SI1145_PARAM_PSLED12SEL_PS1NONE         = 0x00
SI1145_PARAM_PSLED12SEL_PS1LED1         = 0x01
SI1145_PARAM_PSLED12SEL_PS1LED2         = 0x02
SI1145_PARAM_PSLED12SEL_PS1LED3         = 0x04

SI1145_PARAM_PSLED3SEL                  = 0x03
SI1145_PARAM_PSENCODE                   = 0x05
SI1145_PARAM_ALSENCODE                  = 0x06

SI1145_PARAM_PS1ADCMUX                  = 0x07
SI1145_PARAM_PS2ADCMUX                  = 0x08
SI1145_PARAM_PS3ADCMUX                  = 0x09
SI1145_PARAM_PSADCOUNTER                = 0x0A
SI1145_PARAM_PSADCGAIN                  = 0x0B
SI1145_PARAM_PSADCMISC                  = 0x0C
SI1145_PARAM_PSADCMISC_RANGE            = 0x20
SI1145_PARAM_PSADCMISC_PSMODE           = 0x04

SI1145_PARAM_ALSIRADCMUX                = 0x0E
SI1145_PARAM_AUXADCMUX                  = 0x0F

SI1145_PARAM_ALSVISADCOUNTER            = 0x10
SI1145_PARAM_ALSVISADCGAIN              = 0x11
SI1145_PARAM_ALSVISADCMISC              = 0x12
SI1145_PARAM_ALSVISADCMISC_VISRANGE     = 0x20

SI1145_PARAM_ALSIRADCOUNTER             = 0x1D
SI1145_PARAM_ALSIRADCGAIN               = 0x1E
SI1145_PARAM_ALSIRADCMISC               = 0x1F
SI1145_PARAM_ALSIRADCMISC_RANGE         = 0x20

SI1145_PARAM_ADCCOUNTER_511CLK          = 0x70

SI1145_PARAM_ADCMUX_SMALLIR             = 0x00
SI1145_PARAM_ADCMUX_LARGEIR             = 0x03



# REGISTERS
SI1145_REG_PARTID                       = 0x00
SI1145_REG_REVID                        = 0x01
SI1145_REG_SEQID                        = 0x02

SI1145_REG_INTCFG                       = 0x03
SI1145_REG_INTCFG_INTOE                 = 0x01
SI1145_REG_INTCFG_INTMODE               = 0x02

SI1145_REG_IRQEN                        = 0x04
SI1145_REG_IRQEN_ALSEVERYSAMPLE         = 0x01
SI1145_REG_IRQEN_PS1EVERYSAMPLE         = 0x04
SI1145_REG_IRQEN_PS2EVERYSAMPLE         = 0x08
SI1145_REG_IRQEN_PS3EVERYSAMPLE         = 0x10


SI1145_REG_IRQMODE1                     = 0x05
SI1145_REG_IRQMODE2                     = 0x06

SI1145_REG_HWKEY                        = 0x07
SI1145_REG_MEASRATE0                    = 0x08
SI1145_REG_MEASRATE1                    = 0x09
SI1145_REG_PSRATE                       = 0x0A
SI1145_REG_PSLED21                      = 0x0F
SI1145_REG_PSLED3                       = 0x10
SI1145_REG_UCOEFF0                      = 0x13
SI1145_REG_UCOEFF1                      = 0x14
SI1145_REG_UCOEFF2                      = 0x15
SI1145_REG_UCOEFF3                      = 0x16
SI1145_REG_PARAMWR                      = 0x17
SI1145_REG_COMMAND                      = 0x18
SI1145_REG_RESPONSE                     = 0x20
SI1145_REG_IRQSTAT                      = 0x21
SI1145_REG_IRQSTAT_ALS                  = 0x01

SI1145_REG_ALSVISDATA0                  = 0x22
SI1145_REG_ALSVISDATA1                  = 0x23
SI1145_REG_ALSIRDATA0                   = 0x24
SI1145_REG_ALSIRDATA1                   = 0x25
SI1145_REG_PS1DATA0                     = 0x26
SI1145_REG_PS1DATA1                     = 0x27
SI1145_REG_PS2DATA0                     = 0x28
SI1145_REG_PS2DATA1                     = 0x29
SI1145_REG_PS3DATA0                     = 0x2A
SI1145_REG_PS3DATA1                     = 0x2B
SI1145_REG_UVINDEX0                     = 0x2C
SI1145_REG_UVINDEX1                     = 0x2D
SI1145_REG_PARAMRD                      = 0x2E
SI1145_REG_CHIPSTAT                     = 0x30

# I2C Address
SI1145_ADDR                             = 0x60


def read8(address):
    # Read and return a byte from the specified 16-bit register address.
    with device:
        device.write(bytes([(address >> 8) & 0xFF,
                             address & 0xFF]),
                             stop=False)
        #device.write(bytes([address]), stop=False)
        result = bytearray(1)
        device.readinto(result)
        print("read8")
        print(result)
        return result[0]

def read16(address):
    # Read and return a 16-bit unsigned big endian value read from the
    # specified 16-bit register address.
    with device:
        device.write(bytes([(address >> 8) & 0xFF,
                             address & 0xFF]),
                             stop=False)
        #device.write(bytes([address]), stop=False)
        result = bytearray(2)
        device.readinto(result)
        print('read16: {}'.format(hex(address)))
        print(result)
        return (result[0] << 8) | result[1]


def write8( address, data):
    # Write 1 byte of data from the specified 16-bit register address.
    with device:
        device.write(bytes([(address >> 8) & 0xFF,
                             address & 0xFF,
                             data])) 


def readregister(register):
    result = bytearray(REGISTER_SIZE)
        
    i2c.writeto(device, bytes([register]))
    i2c.readfrom_into(device, result)
    
    print('Address {0}: {1}'.format(hex(register), ' '.join([hex(x) for x in result])))
    
    
def writeParam(p, v):
    write8(SI1145_REG_PARAMWR, v)
    write8(SI1145_REG_COMMAND, p | SI1145_PARAM_SET)
    return read8(SI1145_REG_PARAMRD)

def reset():
    write8(SI1145_REG_MEASRATE0, 0)
    write8(SI1145_REG_MEASRATE1, 0)
    write8(SI1145_REG_IRQEN, 0)
    write8(SI1145_REG_IRQMODE1, 0)
    write8(SI1145_REG_IRQMODE2, 0)
    write8(SI1145_REG_INTCFG, 0)
    write8(SI1145_REG_IRQSTAT, 0xFF)

    write8(SI1145_REG_COMMAND, SI1145_RESET)
    time.sleep(.01)
    write8(SI1145_REG_HWKEY, 0x17)
    time.sleep(.01)
def load_calibration():
    # /***********************************/
    # Enable UVindex measurement coefficients!

    write8(SI1145_REG_UCOEFF0, 0x29)
    write8(SI1145_REG_UCOEFF1, 0x89)
    write8(SI1145_REG_UCOEFF2, 0x02)
    write8(SI1145_REG_UCOEFF3, 0x00)

    # Enable UV sensor
    writeParam(SI1145_PARAM_CHLIST, SI1145_PARAM_CHLIST_ENUV | SI1145_PARAM_CHLIST_ENALSIR | SI1145_PARAM_CHLIST_ENALSVIS | SI1145_PARAM_CHLIST_ENPS1)

    # Enable interrupt on every sample
    write8(SI1145_REG_INTCFG, SI1145_REG_INTCFG_INTOE)
    write8(SI1145_REG_IRQEN, SI1145_REG_IRQEN_ALSEVERYSAMPLE)

    # /****************************** Prox Sense 1 */

    # Program LED current
    write8(SI1145_REG_PSLED21, 0x03) # 20mA for LED 1 only
    writeParam(SI1145_PARAM_PS1ADCMUX, SI1145_PARAM_ADCMUX_LARGEIR)

    # Prox sensor #1 uses LED #1
    writeParam(SI1145_PARAM_PSLED12SEL, SI1145_PARAM_PSLED12SEL_PS1LED1)

    # Fastest clocks, clock div 1
    writeParam(SI1145_PARAM_PSADCGAIN, 0)

    # Take 511 clocks to measure
    writeParam(SI1145_PARAM_PSADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK)

    # in prox mode, high range
    writeParam(SI1145_PARAM_PSADCMISC, SI1145_PARAM_PSADCMISC_RANGE | SI1145_PARAM_PSADCMISC_PSMODE)
    writeParam(SI1145_PARAM_ALSIRADCMUX, SI1145_PARAM_ADCMUX_SMALLIR)

    # Fastest clocks, clock div 1
    writeParam(SI1145_PARAM_ALSIRADCGAIN, 0)

    # Take 511 clocks to measure
    writeParam(SI1145_PARAM_ALSIRADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK)

    # in high range mode
    writeParam(SI1145_PARAM_ALSIRADCMISC, SI1145_PARAM_ALSIRADCMISC_RANGE)

    # fastest clocks, clock div 1
    writeParam(SI1145_PARAM_ALSVISADCGAIN, 0)

    # Take 511 clocks to measure
    writeParam(SI1145_PARAM_ALSVISADCOUNTER, SI1145_PARAM_ADCCOUNTER_511CLK)

    # in high range mode (not normal signal)
    writeParam(SI1145_PARAM_ALSVISADCMISC, SI1145_PARAM_ALSVISADCMISC_VISRANGE)

    # measurement rate for auto
    write8(SI1145_REG_MEASRATE0, 0xFF) # 255 * 31.25uS = 8ms

    # auto run
    write8(SI1145_REG_COMMAND, SI1145_PSALS_AUTO)


def readUV():
	return read16(0x2C)

#returns visible + IR light levels
def readVisible():
    return read16(0x22)

#returns IR light levels
def readIR():
    return read16(0x24)

# Returns "Proximity" - assumes an IR LED is attached to LED
def readProx():
    return read16(0x26)

# Initialize and lock the I2C bus.
i2c = busio.I2C(board.SCL, board.SDA)
#while not i2c.try_lock():
#    pass

# Find the first I2C device available.
#devices = i2c.scan()
#while len(devices) < 1:
#    devices = i2c.scan()
#device = devices[0]

#print('Found device with address: {}'.format(hex(device)))

# Assuming the first one found is the only one attached and is the UV sensor!


#readregister(0x2C)

device = I2CDevice(i2c, 0x60)
reset()
load_calibration()

#with device:
#     device.write(bytes([0x2C]), stop=False)
#     result = bytearray(2)
#     device.readinto(result)
#     print(result)

#while 1:
print("readuv")
print(readUV())
print("readvisible")
print(readVisible())
print("readIR")
print(readIR())
print("readProx")
print(readProx())
#time.sleep(1)

#i2c.writeto(device, bytes([0x2C]))
#i2c.readfrom_into(device, result)
#print('UV Address {0}: {1}'.format(hex(0x2C), ' '.join([hex(x) for x in result])))
# Unlock the I2C bus when finished.  Ideally put this in a try-finally!
i2c.unlock()