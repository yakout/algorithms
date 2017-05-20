.PHONY: all clean
CC=gcc
CPP=g++
AR=ar
RANLIB=ranlib
CFLAGS= -g -Wall -Wno-unused-function
C11FLAGS= -g -Wall -Wno-unused-function -std=c++0x
SRCDIR = ./src
INCLUDEDIR = -I./include -I.
DEPS = 
LIBS = -lm

PROGRAMS = test

all: $(PROGRAMS)

test: $(SRCDIR)/hashing_driver.cpp
	$(CPP) $(C11FLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)
clean:
	rm -rf $(PROGRAMS) *.dSYM
