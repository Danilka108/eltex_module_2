CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
OBJECTS=main.o person.o
EXECUTABLE=task_6_1

all: clean build

.PHONY: run
run: clean build
	./$(EXECUTABLE)

.PHONY: build
build: $(OBJECTS) libcontacts.a
	$(CC) $(OBJECTS) -L. -lcontacts -o $(EXECUTABLE)

libcontacts.a: contacts.o
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -rf *.o *.a $(EXECUTABLE)
