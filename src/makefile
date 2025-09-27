# Authors: Yasir Jami & Cole Doris 

# EXAMPLE USAGE OF GLOBBING: ./findme . -name "*.c"
# If using a glob, name argument must be enclosed in quotes
# Otherwise, name argument is expanded and substituted to the first filename in the current directory that matches the glob
# Quotes are not necessary if you are just looking for a file name (-name main.c is fine)
procsim_OBJS:=dStruct.o procLib.o
INC:=-I/../include/

all: procSim

CC:=gcc
CFLAGS:=-Wall -pthread

procSim: $(procsim_OBJS)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o procSim 
