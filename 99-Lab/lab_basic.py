import time
import datetime
import board
import busio

# Create library object using our Bus I2C port
i2c = busio.I2C(board.SCL, board.SDA)

from Adafruit7Segment import SevenSegment
#segment = SevenSegment.SevenSegment(address=0x70)
#segment.begin()

segment = SevenSegment.SevenSegment(address=0x71) # default is 0x70
segment.begin()

print("Press CTRL+Z to exit")

cnt1 = 0


while True:
    now = datetime.datetime.now()
    hour = now.hour
    minute = now.minute
    second = now.second

    segment.clear()
    # Set hours
    segment.set_digit(0, int(hour/10))     # Tens
    segment.set_digit(1, hour%10)     # Tens
    segment.set_colon(second % 2)
    
    # Set minutes
    segment.set_digit(2, int(minute / 10))   # Tens
    segment.set_digit(3, minute % 10)        # Ones

    # Toggle colon
    segment.set_colon(second % 2)            # Toggle colon at 1Hz

    # Write the display buffer to the hardware.  This must be called to
    # update the actual display LEDs.
    segment.write_display()
    time.sleep(1.0)
    cnt1 = cnt1 + 1
    print('{}{}:{}{}:{:02d}'.format(int(hour/10), hour%10, int(minute / 10), minute % 10, second))




