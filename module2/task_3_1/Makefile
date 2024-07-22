CC=gcc
# CFLAGS=-Wall -Werror -Wextra
CFLAGS=
SRCS=main.c parser.c
OBJS=$(SRCS:%.c=%.o)
EXECUTABLE=task_3_1

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

main.o: parser.h
parser.o: parser.h

clean:
	rm -f *.o *.so *.a $(EXECUTABLE)
