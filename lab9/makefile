# Yasir Jami (3077942)
# CMPT 360 Lab 9

CC:=gcc
CFLAGS:= -Wall # may not use std=c11, may run into issues functionality for sys/stat.h (at least from what I remember from lab 3)

findme: main.o findme.o 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o findme
