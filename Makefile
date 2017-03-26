.PHONY: all clean
CC=gcc
CPP=Clang
AR=ar
RANLIB=ranlib
CFLAGS= -g -Wall -Wno-unused-function
C11FLAGS= -g -Wall -Wno-unused-function -std=c++11
SRCDIR = ./src
INCLUDEDIR = -I./include -I.
DEPS = 
LIBS = -lm

PROGRAMS = test

all: $(PROGRAMS)

test: $(SRCDIR)/test.cpp
	$(CPP) $(C11FLAGS) -o $@ $^ $(INCLUDEDIR) $(LIBS)
clean:
	rm -rf $(PROGRAMS) *.dSYM
