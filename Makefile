#
# Copyright (C) 2001 Vasili Gavrilov <vgavrilov AAAATTTTT users.sourceforge.net>
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

SHELL=/bin/sh

BIN=your_project_name

OS=$(shell uname)
ifeq ($(findstring CYGWIN,$(OS)),CYGWIN)
	OS=Cygwin
endif
ifeq ($(findstring WINNT,$(OS)),WINNT)
	OS=Cygwin
endif

ifeq ($(OS), Cygwin)
	NOCYGWIN= -mno-cygwin
	#fix for recently introduced problem 
	SHELL=c:/cygwin/bin/bash.exe
endif

#consider all *.c as sources  
SOURCES.c := $(wildcard *.c)


CFLAGS= $(NOCYGWIN) -ansi -W -Wall
CPPFLAGS=
CC=gcc
SLIBS=
INCLUDES=
OBJS=$(SOURCES.c:.c=.o)
LINK=gcc $(CFLAGS)
LFLAGS=-lm $()

debug : CFLAGS = $(NOCYGWIN) -ansi -W -Wall -g -Wundef
pedantic : CFLAGS = $(NOCYGWIN) -ansi -W -Wall -g -Wundef -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations
release : CFLAGS = $(NOCYGWIN) -ansi -W -Wall -O2
ut : CFLAGS = $(NOCYGWIN) -ansi -g -DUNIT_TEST -DHASH_UNIT_TEST

.SUFFIXES:
.SUFFIXES: .d .o .h .c
.c.o: ; $(CC) $(INCLUDES) $(CFLAGS) -MMD -c $*.c 

.PHONY: clean

%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

all release debug pedantic ut ut1: $(BIN)

$(BIN): $(OBJS)
	$(LINK) $(FLAGS) -o $(BIN) $(OBJS) $(LFLAGS)

clean:
	rm -f $(BIN) $(OBJS) *.d *~


include $(sources:.c=.d)
