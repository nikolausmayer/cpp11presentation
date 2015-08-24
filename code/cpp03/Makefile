##
# The MIT License (MIT)
# 
# Copyright (c) 2015 Nikolaus Mayer
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
##


## Where to look for includes (default is 'here')
INCLUDE_DIRS ?= -I. 

## Compiler
CXX ?= g++

## Compiler flags; extended in 'debug'/'release' rules
CXXFLAGS ?= -W -Wall -Wextra -Wpedantic

## Linker flags
LDFLAGS ?= 

## Default name for the built executable
TARGET = main

## Every *.c* file is a source file
SRCS = $(wildcard *.c*)
## Every *.h* file is a source file
HEADERS = $(wildcard *.h*)


## Build a *.o object file for every source file
OBJS = $(addsuffix .o, $(basename $(SRCS)))


## Tell make that e.g. 'make clean' is not supposed to create a file 'clean'
##
## "Why is it called 'phony'?" -- because it's not a real target. That is, 
## the target name isn't a file that is produced by the commands of that target.
.PHONY: all clean debug release


## Default is release build mode
all: release
	
## When in debug mode, don't optimize, and create debug symbols
debug: CXXFLAGS += -O0 -g
debug: $(TARGET)
	
## When in release mode, optimize
release: CXXFLAGS += -O3
release: $(TARGET)

## Remove built object files and the main executable
## The dash ("-") in front of "rm" tells make to ignore errors. In this
## case, executing "make clean" does not error-terminate when no object
## file or executable is found (which would be the usual behaviour).
clean:
	$(info ... deleting built object files and executable  ...)
	-rm *.o $(TARGET) 

## The main executable depends on all object files of all source files
$(TARGET): $(OBJS)
	$(info ... linking $@ ...)
	$(CXX) $^ $(LDFLAGS) -o $@

## Every object file depends on its source and the makefile itself,
## and on all header files (just to make sure that header changes
## prompt recompilation; actually this is totally overkill)
%.o: %.c Makefile $(HEADERS)
	$(info ... compiling $@ ...)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

%.o: %.cc Makefile $(HEADERS)
	$(info ... compiling $@ ...)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

%.o: %.cpp Makefile $(HEADERS)
	$(info ... compiling $@ ...)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

