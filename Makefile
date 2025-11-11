TARGET=game.exe
LIBS=-lraylib
CC=g++
CFLAGS=-Wall -Wextra -Wfloat-conversion

OBJECTS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS=$(wildcard *.hpp)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) $(LIBS) -o $@
	-rm -f *.o

.PHONY: default all clean run

default: $(TARGET)
all: default
run: all
	./$(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)
