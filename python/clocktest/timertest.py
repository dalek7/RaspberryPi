from datetime import datetime
import time

cnt = 0
while(1):
    t = datetime.now()
    # t = datetime.time(datetime.now())
    cnt = cnt+1
    print('{}\t{}'.format(cnt, t))
    time.sleep(10)  