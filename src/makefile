# Authors: Yasir Jami & Cole Doris

CC:= gcc
CFLAGS:=-Wall -std=c11
SOURCE:=./src/
OBJECT:=../obj/

procSim: procSim.o procLib.o dStruct.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

$(OBJECT)%.o: $(SOURCE)%.c
	$(CC) $(CFLAGS) -c $< -o $@ -lm

# For testing specific behavior 
#app: test.o dStruct.o
#	$(CC) -o $@ $(CFLAGS) $^

.PHONY: clean

clean:
	rm -f *.o app procSim
cleanlog:
	rm -f ../log/logfile*
