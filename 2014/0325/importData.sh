#!/bin/bash

#variable
ip_addr='127.0.0.1'
prot='

# This program check tomcat and import data into database.
if [ -f ImportData.class ] ; then
    java -classpath /home/ice/WebSite/WEB-INF/lib/socketding.jar:/home/ice/WebSite/WEB-INF/lib/commons-lang-2.4.jar:. ImportData 192.168.99.86 5555 /home/ice/Backup/datasync
else
    javac ImportData.java -classpath /home/ice/WebSite/WEB-INF/lib/socketdin
g.jar
    java -classpath /home/ice/WebSite/WEB-INF/lib/socketding.jar:/home/ice/WebSite/WEB-INF/lib/commons-lang-2.4.jar:. ImportData 192.168.99.86 5555 /home/ice/Backup/datasync
fi

