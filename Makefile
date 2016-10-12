# generic makefile

CC = clang++
EXT = cpp
HEXT = h

# flags
LIB = -lm
MAINLIB=
FLAGS = -Wall -std=c++11
DLL_FLAGS= 

MODE = debug
# release or debug

ifeq ($(MODE), release)
FLAGS += -O2
else
FLAGS += -O0 -g
endif

# modules
INCLUDE_DIR=/usr/include
THIRD_PARTY_DIR=

MODULES = lexer parser

# Everything after this is generic, no need to edit
VPATH = src $(addprefix src/,$(THIRD_PARTY_DIR)) $(INCLUDE_DIR)
INCLUDE = -Isrc $(addprefix -I,$(INCLUDE_DIR))
SOURCES = $(addsuffix .$(EXT),$(MODULES))
OBJS = $(SOURCES:%.$(EXT)=bin/%.o)

.PHONY: all run clean
  
all: bin/main

bin/main: bin/main.o $(OBJS) 
	$(CC) -o bin/main bin/main.o $(OBJS) $(FLAGS) $(LIB) -Llib -Wl,-rpath=lib $(MAINLIB)

bin/main.o: src/main.cpp
	$(CC) -c -o bin/main.o src/main.cpp $(FLAGS) $(INCLUDE)

###

run:
	bin/main
	
clean:
	rm -f bin/main bin/*.o

#dependency builder
#depend: .depend

#.depend: $(SOURCES)
#	rm -f ./.depend
#	$(CC) $(CFLAGS) -MM $^ -MF  ./.depend;

#include .depend
#dependency

bin/%.o : %.$(EXT) %.$(HEXT)
	$(CC) -c $< -o $@ $(DLL_FLAGS) $(FLAGS) $(INCLUDE)
