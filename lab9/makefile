# Yasir Jami & Cole Doris 
# CMPT 360 Lab 10

# EXAMPLE USAGE OF GLOBBING: ./findme . -name "*.c"
# If using a glob, name argument must be enclosed in quotes
# Otherwise, name argument is expanded and substituted to the first filename in the current directory that matches the glob
# Quotes are not necessary if you are just looking for a file name (-name main.c is fine)

findme_OBJS:= main.o findme.o
testGlob_OBJS:= testGlob.o

all: findme testGlob

CC:=gcc
CFLAGS:= -Wall -pthread # may not use std=c11, could run into issues while using sys/stat.h

findme: $(findme_OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

testGlob: $(testGlob_OBJS) 
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o findme testGlob
