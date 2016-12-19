import time

print time.localtime()

from time import gmtime, strftime
print strftime("%a, %d %b %Y %H:%M:%S", gmtime())
print time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()) 

count = 0
while True:
    if count % 1000 == 0:
        print count
    count = count + 1
