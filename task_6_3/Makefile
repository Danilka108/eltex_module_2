CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
PICFLAG=-fPIC
OBJECTS=main.o
EXECUTABLE=task_6_3

.PHONY: all run build clean

all: clean build

run: clean build
	./$(EXECUTABLE)

build: $(OBJECTS) libsum.so libsub.so libdiv.so libmul.so
	$(CC) -rdynamic $(OBJECTS) -o $(EXECUTABLE) -ldl

lib%.so: %_pic.o
	$(CC) -shared $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $<

%_pic.o: %.c
	$(CC) $(PICFLAG) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a *.so $(EXECUTABLE)
