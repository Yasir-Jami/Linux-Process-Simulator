# Name: Yasir Jami & Cole Doris
# 360 Lab 1

CC:=gcc
CFLAGS:= -Wall -std=c11

testStruct: testStruct.o dStruct.o
	$(CC) -o $@ $(CFLAGS) $^

%.o: %.c
	$(CC) -c $@ $(CFLAGS) $<

.PHONY: clean

clean:
	rm -f *.o testStruct
