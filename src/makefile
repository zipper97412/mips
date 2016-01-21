LDFLAGS= -g
CFLAGS=-Wall  -g
SRC = src

test : main2.o cpu.o mem.o instructions.o runners.o decodeur.o
	gcc $^ -o $@.e $(LDFLAGS)

%.o : %.c
	gcc $(CFLAGS) -c $^ -o $@

clean :
	rm *.o *.e
