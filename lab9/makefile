# Yasir Jami & Cole Doris 
# CMPT 360 Lab 9

CC:=gcc
CFLAGS:= -Wall -pthread # may not use std=c11, could run into issues while using sys/stat.h

findme: main.o findme.o 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o findme
