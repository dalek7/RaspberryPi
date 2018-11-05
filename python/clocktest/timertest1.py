from datetime import datetime
import time
import numpy as np
import os

def MakeDir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
        
        
def GetTimeString(m = -1):
    if m==0:
        s1 = datetime.now().strftime("%Y%m%d%H%M%S")
    else:
        s1 = datetime.now().strftime("%Y%m%d_%H%M%S")

    return s1


MakeDir('out')
fn1 = 'out/out_'+GetTimeString()+'.txt'
print(fn1)
t0 = datetime.now()

v =[]
v.append(t0)
cnt = 0
while(1):
    
    # t = datetime.time(datetime.now())
    cnt = cnt+1
    if cnt%60 ==0:
        t = datetime.now()
        print('{}\t{}'.format(cnt, t))
        v.append(t)
        np.savetxt(fn1, v, fmt='%s', delimiter='\t')
        v = []
        v.append(t0)
    time.sleep(1)
    
    
    
    