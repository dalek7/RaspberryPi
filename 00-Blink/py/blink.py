import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(16,GPIO.OUT)
while(True):
	print ("LED on")
	GPIO.output(13,GPIO.HIGH)
	GPIO.output(16,GPIO.LOW)
	time.sleep(1)
	print("LED off")
	GPIO.output(13,GPIO.LOW)
	GPIO.output(16,GPIO.HIGH)
	time.sleep(1)