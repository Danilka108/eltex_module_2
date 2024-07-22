CC=gcc
CFLAGS=-c -Wall
OBJECTS=main.o pqueue.o
EXECUTABLE=task_4_2

all: clean build

run: clean build
	./$(EXECUTABLE)

build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o $(EXECUTABLE)
