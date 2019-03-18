# https://sourceforge.net/p/raspberry-gpio-python/wiki/PWM/
# https://www.raspberrypi.org/forums/viewtopic.php?t=111353
import time
import RPi.GPIO as GPIO

led1 = 13
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(led1, GPIO.OUT)

p = GPIO.PWM(led1, 50)  # channel=12 frequency=50Hz
p.start(0)
try:
    while 1:
        for dc in range(0, 101, 5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.1)
        for dc in range(100, -1, -5):
            p.ChangeDutyCycle(dc)
            time.sleep(0.1)
except KeyboardInterrupt:
    pass
p.stop()
GPIO.cleanup()
