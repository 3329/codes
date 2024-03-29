#
# Simple makefile for the sample loadable builtins
#
# Copyright (C) 1996-2009 Free Software Foundation, Inc.     

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Include some boilerplate Gnu makefile definitions.
prefix = /usr/local

exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
infodir = ${datarootdir}/info
includedir = ${prefix}/include

datarootdir = ${prefix}/share

topdir = ../..
BUILD_DIR = /home/young/codes/2014/0418/bash-4.3
srcdir = .
VPATH = .


CC = gcc
RM = rm -f

SHELL = /bin/sh

host_os = linux-gnu
host_cpu = x86_64
host_vendor = unknown

CFLAGS = -g -O2
LOCAL_CFLAGS = 
DEFS = -DHAVE_CONFIG_H
LOCAL_DEFS = -DSHELL

CPPFLAGS = 

BASHINCDIR = ${topdir}/include

LIBBUILD = ${BUILD_DIR}/lib

INTL_LIBSRC = ${topdir}/lib/intl
INTL_BUILDDIR = ${LIBBUILD}/intl
INTL_INC = 
LIBINTL_H = 

CCFLAGS = $(DEFS) $(LOCAL_DEFS) $(LOCAL_CFLAGS) $(CFLAGS)

#
# These values are generated for configure by ${topdir}/support/shobj-conf.
# If your system is not supported by that script, but includes facilities for
# dynamic loading of shared objects, please update the script and send the
# changes to bash-maintainers@gnu.org.
#
SHOBJ_CC = gcc
SHOBJ_CFLAGS = -fPIC
SHOBJ_LD = ${CC}
SHOBJ_LDFLAGS = -shared -Wl,-soname,$@ 
SHOBJ_XLDFLAGS = 
SHOBJ_LIBS = 
SHOBJ_STATUS = supported

INC = -I. -I.. -I$(topdir) -I$(topdir)/lib -I$(topdir)/builtins \
      -I$(BASHINCDIR) -I$(BUILD_DIR) -I$(LIBBUILD) \
      -I$(BUILD_DIR)/builtins $(INTL_INC)

.c.o:
	$(SHOBJ_CC) $(SHOBJ_CFLAGS) $(CCFLAGS) $(INC) -c -o $@ $<


ALLPROG = print truefalse sleep pushd finfo logname basename dirname \
	  tty pathchk tee head mkdir rmdir printenv id whoami \
	  uname sync push ln unlink realpath strftime mypid
OTHERPROG = necho hello cat

all:	$(SHOBJ_STATUS)

supported:	$(ALLPROG)
others:		$(OTHERPROG)

unsupported:
	@echo "Your system (${host_os}) is not supported by the"
	@echo "${topdir}/support/shobj-conf script."
	@echo "If your operating system provides facilities for dynamic"
	@echo "loading of shared objects using the dlopen(3) interface,"
	@echo "please update the script and re-run configure.
	@echo "Please send the changes you made to bash-maintainers@gnu.org"
	@echo "for inclusion in future bash releases."

everything: supported others

print:	print.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ print.o $(SHOBJ_LIBS)

necho:	necho.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ necho.o $(SHOBJ_LIBS)

hello:	hello.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ hello.o $(SHOBJ_LIBS)

truefalse: truefalse.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ truefalse.o $(SHOBJ_LIBS)

sleep:	sleep.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ sleep.o $(SHOBJ_LIBS)

finfo:	finfo.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ finfo.o $(SHOBJ_LIBS)

cat:	cat.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ cat.o $(SHOBJ_LIBS)

logname:	logname.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ logname.o $(SHOBJ_LIBS)

basename:	basename.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ basename.o $(SHOBJ_LIBS)

dirname:	dirname.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ dirname.o $(SHOBJ_LIBS)

tty:	tty.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ tty.o $(SHOBJ_LIBS)

pathchk:	pathchk.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ pathchk.o $(SHOBJ_LIBS)

tee:	tee.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ tee.o $(SHOBJ_LIBS)

mkdir:	mkdir.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ mkdir.o $(SHOBJ_LIBS)

rmdir:	rmdir.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ rmdir.o $(SHOBJ_LIBS)

head:	head.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ head.o $(SHOBJ_LIBS)

printenv:	printenv.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ printenv.o $(SHOBJ_LIBS)

id:	id.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ id.o $(SHOBJ_LIBS)

whoami:	whoami.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ whoami.o $(SHOBJ_LIBS)

uname:	uname.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ uname.o $(SHOBJ_LIBS)

sync:	sync.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ sync.o $(SHOBJ_LIBS)

push:	push.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ push.o $(SHOBJ_LIBS)

ln:	ln.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ ln.o $(SHOBJ_LIBS)

unlink:	unlink.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ unlink.o $(SHOBJ_LIBS)

realpath:	realpath.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ realpath.o $(SHOBJ_LIBS)

strftime:	strftime.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ strftime.o $(SHOBJ_LIBS)

mypid:	mypid.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ mypid.o $(SHOBJ_LIBS)

# pushd is a special case.  We use the same source that the builtin version
# uses, with special compilation options.
#
pushd.c:	${topdir}/builtins/pushd.def
	$(RM) $@
	${BUILD_DIR}/builtins/mkbuiltins -D ${topdir}/builtins ${topdir}/builtins/pushd.def

pushd.o:	pushd.c
	$(RM) $@
	$(SHOBJ_CC) -DHAVE_CONFIG_H -DPUSHD_AND_POPD -DLOADABLE_BUILTIN $(SHOBJ_CFLAGS) $(CFLAGS) $(CPPFLAGS) $(INC) -c -o $@ $<

pushd:	pushd.o
	$(SHOBJ_LD) $(SHOBJ_LDFLAGS) $(SHOBJ_XLDFLAGS) -o $@ pushd.o $(SHOBJ_LIBS)

clean:
	$(RM) $(ALLPROG) $(OTHERPROG) *.o
	-( cd perl && ${MAKE} ${MFLAGS} $@ )

mostlyclean:	clean
	-( cd perl && ${MAKE} ${MFLAGS} $@ )

distclean maintainer-clean: clean
	$(RM) Makefile pushd.c
	-( cd perl && ${MAKE} ${MFLAGS} $@ )

print.o: print.c
truefalse.o: truefalse.c
sleep.o: sleep.c
finfo.o: finfo.c
logname.o: logname.c
basename.o: basename.c
dirname.o: dirname.c
tty.o: tty.c
pathchk.o: pathchk.c
tee.o: tee.c
head.o: head.c
rmdir.o: rmdir.c
necho.o: necho.c
hello.o: hello.c
cat.o: cat.c
printenv.o: printenv.c
id.o: id.c
whoami.o: whoami.c
uname.o: uname.c
sync.o: sync.c
push.o: push.c
mkdir.o: mkdir.c
realpath.o: realpath.c
strftime.o: strftime.c
mypid.o: mypid.c
