#############################################################################
# Makefile for building: libmyku.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.4.3) on: ?? ?? 28 23:14:02 2011
# Project:  ku.pro
# Template: lib
# Command: /opt/qt/bin/qmake -unix -o Makefile ku.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = 
CFLAGS        = -pipe -O2 -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -fPIC $(DEFINES)
INCPATH       = -I/opt/qt/mkspecs/linux-g++ -I.
LINK          = g++
LFLAGS        = -Wl,-rpath,/opt/qt/lib -shared -Wl,-soname,libmyku.so.1
LIBS          = $(SUBLIBS)   -ldl -L.
AR            = ar cqs
RANLIB        = 
QMAKE         = /opt/qt/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ku.cpp 
OBJECTS       = ku.o
DIST          = /opt/qt/mkspecs/common/g++.conf \
		/opt/qt/mkspecs/common/unix.conf \
		/opt/qt/mkspecs/common/linux.conf \
		/opt/qt/mkspecs/qconfig.pri \
		/opt/qt/mkspecs/features/qt_functions.prf \
		/opt/qt/mkspecs/features/qt_config.prf \
		/opt/qt/mkspecs/features/exclusive_builds.prf \
		/opt/qt/mkspecs/features/default_pre.prf \
		/opt/qt/mkspecs/features/release.prf \
		/opt/qt/mkspecs/features/default_post.prf \
		/opt/qt/mkspecs/features/shared.prf \
		/opt/qt/mkspecs/features/dll.prf \
		ku.pro
QMAKE_TARGET  = myku
DESTDIR       = 
TARGET        = libmyku.so.1.0.0
TARGETA       = libmyku.a
TARGETD       = libmyku.so.1.0.0
TARGET0       = libmyku.so
TARGET1       = libmyku.so.1
TARGET2       = libmyku.so.1.0

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  $(TARGET)

$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

Makefile: ku.pro  /opt/qt/mkspecs/linux-g++/qmake.conf /opt/qt/mkspecs/common/g++.conf \
		/opt/qt/mkspecs/common/unix.conf \
		/opt/qt/mkspecs/common/linux.conf \
		/opt/qt/mkspecs/qconfig.pri \
		/opt/qt/mkspecs/features/qt_functions.prf \
		/opt/qt/mkspecs/features/qt_config.prf \
		/opt/qt/mkspecs/features/exclusive_builds.prf \
		/opt/qt/mkspecs/features/default_pre.prf \
		/opt/qt/mkspecs/features/release.prf \
		/opt/qt/mkspecs/features/default_post.prf \
		/opt/qt/mkspecs/features/shared.prf \
		/opt/qt/mkspecs/features/dll.prf
	$(QMAKE) -unix -o Makefile ku.pro
/opt/qt/mkspecs/common/g++.conf:
/opt/qt/mkspecs/common/unix.conf:
/opt/qt/mkspecs/common/linux.conf:
/opt/qt/mkspecs/qconfig.pri:
/opt/qt/mkspecs/features/qt_functions.prf:
/opt/qt/mkspecs/features/qt_config.prf:
/opt/qt/mkspecs/features/exclusive_builds.prf:
/opt/qt/mkspecs/features/default_pre.prf:
/opt/qt/mkspecs/features/release.prf:
/opt/qt/mkspecs/features/default_post.prf:
/opt/qt/mkspecs/features/shared.prf:
/opt/qt/mkspecs/features/dll.prf:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile ku.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/myku1.0.0 || $(MKDIR) .tmp/myku1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/myku1.0.0/ && (cd `dirname .tmp/myku1.0.0` && $(TAR) myku1.0.0.tar myku1.0.0 && $(COMPRESS) myku1.0.0.tar) && $(MOVE) `dirname .tmp/myku1.0.0`/myku1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/myku1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) $(TARGET0) $(TARGET1) $(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


compiler_clean: 

####### Compile

ku.o: ku.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ku.o ku.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

