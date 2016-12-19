#!/usr/bin/env python

import os, time, sys, random

DATA_FILE = "/home/young/data.txt"
DATA_NUMBER = 200000


# 1. generator line data

#def generateData(fp, nums):
def generateData(nums):
    for i in range(nums):
        linedata = str(random.randint(1, 5000)) + ',' + ''.join(["f2_", str(random.randint(222, 111100))]) + ',' + ''.join(["f3_", str(random.randint(12, 111100))]) + ',' + str(random.randint(1, 5000)) + ',' + str(random.randint(333, 666666))
        print linedata
    


if __name__ == '__main__':
    #fp = open(DATA_FILE, 'w+')
    #generateData(fp, DATA_NUMBER)
    generateData(DATA_NUMBER)
    #fp.close()
    
