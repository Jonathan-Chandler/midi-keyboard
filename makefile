ECHO = echo
MAKE = mingw32-make
# CC = mingw32-g++.exe
CC = g++.exe
CFLAGS = -Wall -std=c++17
LIBS = -L../../lib -lwinmm -lsfml-graphics -lsfml-window -lsfml-system

export ECHO
export CC
export INCLUDES
export CFLAGS
export LIBS

all: $(OBJS)
	rm -rf build/midi/*
	rm -rf bin/*.exe
	rm -rf midi.exe
	mkdir -p build/midi/
	mkdir -p bin
	$(MAKE) -C ./src/midi all
#	$(MAKE) -C ./src/unit_tests all

clean:
	$(MAKE) -C ./src/midi clean
#	$(MAKE) -C ./src/unit_tests clean

