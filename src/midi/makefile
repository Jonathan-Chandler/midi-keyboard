INCLUDES = -I../../inc/midi -I../../inc
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:%.cpp=../../build/midi/%.o)
OBJ_NAME = ../../bin/midi.exe

../../build/midi/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS)

all: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(OBJ_NAME) $(LIBS)

clean:
	rm -f ../../build/midi/*
	rm -f $(OBJ_NAME)

