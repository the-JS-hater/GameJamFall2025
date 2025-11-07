TARGET=game.exe
LIBS=-lraylib
CC=g++
CFLAGS=-Wall

OBJECTS=$(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS=$(wildcard *.h)

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
