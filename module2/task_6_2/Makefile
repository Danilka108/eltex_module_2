CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
PICFLAG=-fPIC
OBJECTS=main.o person.o
EXECUTABLE=task_6_2

.PHONY: all run build clean

all: clean build

run: clean build
	./$(EXECUTABLE)

build: $(OBJECTS) libcontacts.so
	$(CC) -rdynamic $(OBJECTS) -o $(EXECUTABLE) -ldl

libcontacts.so: contacts_pic.o person_pic.o
	$(CC) -shared $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

%_pic.o: %.c
	$(CC) $(PICFLAG) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a *.so $(EXECUTABLE)
