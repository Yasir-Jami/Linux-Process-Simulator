# Name: Yasir Jami & Cole Doris
# 360 Lab 2 (Group 4)

CC:= gcc
CFLAGS:=-Wall -std=c11
SOURCE:=./src/
OBJECT:=../obj/

# If using source path, do $(SOURCE)

procSim: procSim.o procLib.o dStruct.o
	$(CC) -o $@ $(CFLAGS) $^

$(OBJECT)%.o: $(SOURCE)%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o procSim ../log/logfile.txt
