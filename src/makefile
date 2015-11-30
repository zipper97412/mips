
SRC = src

test : main.o cpu.o mem.o
	gcc $^ -o $@.e

%.o : %.c
	gcc -g -Wall -c $^ -o $@

clean :
	rm *.o *.e
