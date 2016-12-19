#!/usr/bin/env python
import optparse
from storm.locals import *
from scapy import srp,Ether,ARP,conf

class NetworkRecord(object):
    __storm_table__ = "networkrecord"
    id = Int(primary=True)
    ip = RawStr()
    mac = RawStr()
    hostname = RawStr()

def arping(iprange="10.0.1.0/24"):
    """Arping function takes IP Address or Network, returns nested mac/ip list"""

    conf.verb=0
    ans,unans=srp(Ether(dst="ff:ff:ff:ff:ff:ff")/ARP(pdst=iprange),
              timeout=2)
    collection = []
    for snd, rcv in ans:
        result = rcv.sprintf(r"%ARP.psrc% %Ether.src%").split()
        collection.append(result)
    return collection

def main():
    """Runs program and handles command line options"""

    p = optparse.OptionParser(description='Finds MacAddr of IP address(es)',
                                    prog='pyarping',
                                    version='pyarping 0.1',
                                    usage= '%prog [10.0.1.1 or 10.0.1.0/24]')

    options, arguments = p.parse_args()
    if len(arguments) == 1:
        database = create_database("sqlite:")
        store = Store(database)
        store.execute("CREATE TABLE networkrecord "
            "(id INTEGER PRIMARY KEY, ip VARCHAR,\
                mac VARCHAR, hostname VARCHAR)")
        values = arping(iprange=arguments)
        machine = NetworkRecord()
        store.add(machine)
        #Creates Records
        for ip, mac in values:
            machine.mac = mac
            machine.ip = ip
        #Flushes to database
        store.flush()
        #Prints Record
        print "Record Number: %r" % machine.id
        print "Mac Address: %r" % machine.mac
        print "IP Address: %r" % machine.ip
    else:
        p.print_help()

if __name__ == '__main__':
    main()






