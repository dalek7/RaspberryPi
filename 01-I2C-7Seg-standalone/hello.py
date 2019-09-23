import time
import datetime
import sys

from Adafruit7Segment import SevenSegment
segment = SevenSegment.SevenSegment(address=0x70)

# Initialize the display. Must be called once before using the display.
segment.begin()

print("Press CTRL+Z to exit")

# Continually update the time on a 4 char, 7-segment display
cnt1 = 0
testDev = False
while(True):
  now = datetime.datetime.now()
  hour = now.hour
  minute = now.minute
  second = now.second
    
  segment.clear()
  # Set hours
  cnt1 = cnt1 % 100

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
  # Toggle colon
  #segment.set_colon(second % 2)              # Toggle colon at 1Hz

  # Write the display buffer to the hardware.  This must be called to
  # update the actual display LEDs.
  segment.write_display()

  # Wait a quarter second (less than 1 second to prevent colon blinking getting$
  #time.sleep(0.25)
  time.sleep(1.0)
  cnt1 = cnt1 + 1
