LDFLAGS= -g
CFLAGS=-Wall  -g
SRC = src

emul-mips : mips

mips : main.o cpu.o mem.o instructions.o runners.o decodeur.o
	gcc $^ -o $@.e $(LDFLAGS)

%.o : %.c
	gcc $(CFLAGS) -c $^ -o $@

clean :
	rm *.o *.e
