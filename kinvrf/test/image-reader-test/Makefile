######################################################################
## Filename:      Makefile
## Copyright:     2013, Zhicong Chen
## Version:       
## Author:        Zhicong Chen <zhicong.chen@changecong.com>
## Created at:    Sat Oct 26 23:54:32 2013
## Modified at:   Sat Oct 26 23:55:24 2013
## Modified by:   Zhicong Chen <zhicong.chen@changecong.com>
## Status:        Experimental, do not distribute.
## Description:   
##
#####################################################################

CC=g++
CFLAGES=-ggdb -Wall -c
LFLAGES=
OPENCVCFLAGES = `pkg-config --cflags opencv `
OPENCVLFLAGES = `pkg-config --libs opencv `
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.CPP=.o)
EXECUTABLE=
MAKE=make


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $()