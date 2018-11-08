# https://sourceforge.net/p/raspberry-gpio-python/wiki/PWM/
# https://www.raspberrypi.org/forums/viewtopic.php?t=111353
import time
import RPi.GPIO as GPIO

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(12, GPIO.OUT)

freq = 1000
p = GPIO.PWM(12, freq)  # channel=12 frequency=50Hz
p.start(50) # duty (0~99)
input('Press return to stop:')   # use raw_input for Python 2
p.stop()

GPIO.cleanup()
