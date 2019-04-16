import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM) ## set up BCM GPIO numbering 
GPIO.setwarnings(False)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(16,GPIO.OUT)

GPIO.output(13,GPIO.LOW)
GPIO.output(16,GPIO.LOW)

# Pull-ups
# https://raspi.tv/2013/rpi-gpio-basics-6-using-inputs-and-outputs-together-with-rpi-gpio-pull-ups-and-pull-downs
GPIO.setup(19,GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(20,GPIO.IN, pull_up_down=GPIO.PUD_UP)
#GPIO.setup(21,GPIO.IN)


while(True):
    
    sw1 = GPIO.input(19)
    sw2 = GPIO.input(20)
    print('SW1:{}\tSW2:{}'.format(sw1, sw2))
    
    GPIO.output(13,sw1)
    GPIO.output(16,sw2)
    
    time.sleep(1)
    
    '''
    print ("LED on")
    GPIO.output(13,GPIO.HIGH)
    GPIO.output(16,GPIO.LOW)
    time.sleep(1)
    print("LED off")
    GPIO.output(13,GPIO.LOW)
    GPIO.output(16,GPIO.HIGH)
    '''