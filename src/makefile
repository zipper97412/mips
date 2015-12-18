LDFLAGS= -g
CFLAGS=-Wall -O -g
SRC = src

test : main2.o cpu.o mem.o instructions.o runners.o
	gcc $^ -o $@.e $(LDFLAGS)

decodeur : decodeur.o main.o 
	gcc -o $@.e $^ $(LDFLAGS)

%.o : %.c
	gcc $(CFLAGS) -c $^ -o $@

clean :
	rm *.o *.e
