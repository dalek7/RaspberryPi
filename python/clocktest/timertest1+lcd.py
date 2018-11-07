from datetime import datetime
import time
import numpy as np
import os
from Adafruit_LED_Backpack import SevenSegment

def MakeDir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
        
        
def GetTimeString(m = -1):
    if m==0:
        s1 = datetime.now().strftime("%Y%m%d%H%M%S")
    else:
        s1 = datetime.now().strftime("%Y%m%d_%H%M%S")

    return s1


# 7-segment
segment = SevenSegment.SevenSegment(address=0x70)
segment.begin()


MakeDir('out')
fn1 = 'out/out_'+GetTimeString()+'.txt'
print(fn1)
t0 = datetime.now()

v =[]
v.append(t0)
cnt = 0
fcnt = 0
segment.clear()

segment.set_digit(0, 0)
segment.set_digit(1, 0)
segment.set_digit(2, 0)
segment.set_digit(3, 0)
segment.write_display()
print('System started..')
while(1):
    
    # t = datetime.time(datetime.now())
    
    if cnt%60 ==0:
        segment.clear()
        t = datetime.now()
        print('{}\t{}'.format(cnt, t))
        v.append(t)
        np.savetxt(fn1, v, fmt='%s', delimiter='\t')
        v = []
        v.append(t0)
        
        
        
        if fcnt>99:
            segment.set_digit(1, int(fcnt/100))     # Tens
        
        if fcnt>999:
            segment.set_digit(0, int(fcnt/1000))     # Tens
            
        segment.set_digit(2, int(fcnt/10))     # Tens
        segment.set_digit(3, fcnt%10)     # Tens
        segment.write_display()
        fcnt = fcnt+1
        
    cnt = cnt+1    
    time.sleep(1)
    
    
    
    