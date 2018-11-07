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

bDbg = True
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
        
        v.append(t)
        np.savetxt(fn1, v, fmt='%s', delimiter='\t')
        v = []
        v.append(t0)
        
        val1 = int(fcnt/100) % 10
        val0 = int(fcnt/1000) %10
        val2 = int(fcnt/10) %10
        val3 = fcnt%10
        
        if bDbg:
            print('{}\t{}\t{}---->{}_{}_{}_{}'.format(cnt, t, fcnt, val0, val1, val2, val3))
        
        if fcnt>999:
            segment.set_digit(0, val0)     
            
        if fcnt>99:
            segment.set_digit(1, val1)     
            
        segment.set_digit(2, val2)     
        segment.set_digit(3, val3)     
        segment.write_display()
        fcnt = fcnt+1
        if fcnt>9999:
            cnt = 0
            fcnt = 0
        
    cnt = cnt+1    
    time.sleep(1)