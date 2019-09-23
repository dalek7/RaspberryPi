import time
import datetime

import RPi.GPIO as GPIO
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


import board
import busio
# Create library object using our Bus I2C port
from adafruit_htu21d import HTU21D
i2c = busio.I2C(board.SCL, board.SDA)
sensor = HTU21D(i2c)

from Adafruit7Segment import SevenSegment
segment = SevenSegment.SevenSegment(address=0x70)
segment.begin()

segment1 = SevenSegment.SevenSegment(address=0x71)
segment1.begin()

print("Press CTRL+Z to exit")

cnt1 = 0
testDev = False



while True:
	sw1 = GPIO.input(19)
	sw2 = GPIO.input(20)
	print('SW1:{}\tSW2:{}'.format(sw1, sw2))

	temp = sensor.temperature
	rhum = sensor.relative_humidity

	  
	print("\nTemperature: {0:.2f}".format(temp))
	print("Humidity: {0:.2f}".format(rhum))

	now = datetime.datetime.now()
	hour = now.hour
	minute = now.minute
	second = now.second

	segment.clear()
	# Set hours
	#cnt1 = cnt1 % 60

	#int intTemp = temp * 100;

	if testDev:
		segment.set_digit(0, int(cnt1/10))     # Tens
		segment.set_digit(1, cnt1%10)     # Tens
	else:
		
		segment.set_digit(0, int(hour/10))     # Tens
		segment.set_digit(1, hour%10)     # Tens
		segment.set_colon(second % 2) 
		# Set minutes
		segment.set_digit(2, int(minute / 10))   # Tens
		segment.set_digit(3, minute % 10)        # Ones

		
		#if cnt1%60<30:
		if sw1==0:
			segment1.print_float(temp, decimal_digits=1)
		else:
			segment1.print_float(rhum, decimal_digits=1)
		
		GPIO.output(13,sw1)
		
	# Toggle colon
	#segment.set_colon(second % 2)              # Toggle colon at 1Hz

	# Write the display buffer to the hardware.  This must be called to
	# update the actual display LEDs.
	segment.write_display()
	segment1.write_display()
	# Wait a quarter second (less than 1 second to prevent colon blinking getting$
	#time.sleep(0.25)
	time.sleep(1.0)
	cnt1 = cnt1 + 1




