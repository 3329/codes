#!/usr/bin/env python
import time, random, string

print "Start : %s" %time.ctime()
time.sleep(1)
print "End   : %s" %time.ctime()


for i in range(50):
    #print random.randint(10, 50)
    print random.randrange(10, 50, 2)
