#!/usr/bin/env python 

import os, time

#/home/young/Jimo_Servers2/docstore.exe
#-ip 192.168.99.184 -config /home/young/Jimo_Servers2/proxy_tmp/2_config.txt 
#<0x11956180:2016-04-25 15:31:21:Process.cpp:190> run command (cube): ; logic_pid: 3: exe_path: 
#/home/young/Jimo_Servers2/cube.exe
#-ip 192.168.99.184 -config /home/young/Jimo_Servers2/proxy_tmp/3_config.txt 
#<0x11956180:2016-04-25 15:31:21:Process.cpp:190> run command (frontend): ; logic_pid: 4: exe_path: 
#/home/young/Jimo_Servers2/frontend.exe
#-ip 192.168.99.184 -config /home/young/Jimo_Servers2/proxy_tmp/4_config.txt 

# now 3 machines test
EXE_PATHS = ["Jimo_Servers0", "Jimo_Servers1", "Jimo_Servers2"]
EXE_NAMES = ["docstore.exe", "cube.exe"]


for path in EXE_PATHS:
    for exename in EXE_NAMES:
        exe_abs_path = "/home/young/" + path + "/" + exename
        logfile = path + "_" + exename + "_log.txt"

        config_file = ""
        if (exename == "docstore.exe"):
            config_file = "/home/young/" + path + "/proxy_tmp/2_config.txt"
        if (exename == "cube.exe"):
            config_file = "/home/young/" + path + "/proxy_tmp/3_config.txt"
        config = " -ip 192.168.99.184 -config " + config_file
        # print exe_abs_path
        # print logfile
        testcmd = "valgrind --leak-check=full --log-file=" + logfile + " " + exe_abs_path + config;
        # print testcmd 
        #os.system(testcmd)
