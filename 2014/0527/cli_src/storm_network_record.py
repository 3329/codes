#!/usr/bin/env python
from storm.locals import *

class NetworkRecord(object):
    __storm_table__ = "networkrecord"
    id = Int(primary=True)
    ip = Unicode()
    mac = Unicode()
    hostname = Unicode()

database = create_database("sqlite:")
store = Store(database)
store.execute("CREATE TABLE networkrecord "
    "(id INTEGER PRIMARY KEY, ip VARCHAR, mac VARCHAR, hostname VARCHAR)")
aix = NetworkRecord()
aix.hostname = u"aix.example.com"

store.add(aix)
store.flush()
print "%r, %r" % (aix.id, aix.hostname)





