#!/usr/bin/env python 

import string
from random import Random

def random_str(randomlength=4):
    str = ''
    chars = 'AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789'
    length = len(chars) - 1
    random = Random()
    for i in range(randomlength):
        str+=chars[random.randint(0, length)]
    return str


def random_num(min_num=0, max_num=10000):
    random = Random()
    return random.randint(min_num, max_num)


if __name__ == '__main__':
    for records_num in range(50):
        print "%d,,key2%s,,key3%s,,key4%s,,key5%s" %(random_num(), random_str(), random_str(), random_str(), random_str())

