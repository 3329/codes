#!/usr/bin/env python
import subprocess
import re
def arping(ipaddress="10.0.1.1"):
    """Arping function takes IP Address or Network, returns nested mac/ip list"""

    #Assuming use of arping on Red Hat Linux
    p = subprocess.Popen("/usr/sbin/arping -c 2 %s" % ipaddress, shell=True,
                        stdout=subprocess.PIPE)
    out = p.stdout.read()
    result = out.split()
    pattern = re.compile(":")
    for item in result:
        if re.search(pattern, item):
            print item
arping()

