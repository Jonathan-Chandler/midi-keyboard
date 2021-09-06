ECHO = echo
MAKE = mingw32-make
# CC = mingw32-g++.exe
CC = g++.exe
CFLAGS = -Wall -std=c++17
LIBS = -lwinmm

export ECHO
export CC
export INCLUDES
export CFLAGS
export LIBS

all: $(OBJS)
	rm -rf build/midi/*
	rm -rf midi.exe
	mkdir -p build/midi/
	$(MAKE) -C ./src/midi all
#	$(MAKE) -C ./src/unit_tests all

clean:
	$(MAKE) -C ./src/midi clean
#	$(MAKE) -C ./src/unit_tests clean

