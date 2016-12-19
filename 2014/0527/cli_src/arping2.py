#!/usr/bin/env python

import optparse
from scapy import srp,Ether,ARP,conf

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

    p = optparse.OptionParser(description='Finds Mac Address of IP address(es)',
                                    prog='pyarping',
                                    version='pyarping 0.1',
                                    usage='%prog [10.0.1.1 or 10.0.1.0/24]')
    p.add_option('-m', '--mac', action='store_true', help='returns only mac address')
    p.add_option('-v', '--verbose', action='store_true', help='returns verbose output')

    options, arguments = p.parse_args()
    if len(arguments) == 1:
        values = arping(iprange=arguments)
        if options.mac:
            for ip, mac in values:
                print mac
        elif options.verbose:
            for ip, mac in values:
                print "IP: %s MAC: %s " % (ip, mac)
        else:
            for ip, mac in values:
                print ip, mac


    else:
        p.print_help()

if __name__ == '__main__':
    main()


