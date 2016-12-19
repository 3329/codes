SOURCES=thmain.cpp tthread.cpp
include demo.mk
CFLAGS=-lpthread -g

HEADERS:=$(SOURCES) tthread.h
HEADERS?=Hello
CC=gcc
define cmd
ls
pwd
endef

VAR2:=$(SOURCES:.cpp=.o)
demo:$(SOURCES)
#	g++ $(SOURCES) -omain $(CFLAGS)
#	echo $(HEADERS)
#	$(cmd)
#	echo $(MAKEFILE_LIST)
#	echo $(CC)
#	echo $(CXX)
#	$(RM) main demo
#	@echo $(@D)
#	@echo $(<F)
#	@echo $+
#	@echo $?
#	@echo $^
	@echo $(VAR2)

