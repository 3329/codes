#!/usr/bin/env python
import ConfigParser

def readConfig(file="config.ini"):
    Config = ConfigParser.ConfigParser()
    Config.read(file)
    sections = Config.sections()
    for machine in sections:
        #uncomment line below to see how this config file is parsed
        #print Config.items(machine)
        macAddr = Config.items(machine)[0][1]
        print machine, macAddr
readConfig()

