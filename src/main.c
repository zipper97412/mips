#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodeur.h"

const char *tab[]= {
	"ADDI $t0, $zero, 5",
	"ADD $t2, $t0, $t1",
	"SUB $t3, $t0, $t2",
	"MULT $t3,$t0",
	"MULT $t3,$t0",
	"MFHI $t4",
	"MFLO $t5",
	"DIV $t0, $t3",
	"MFLO $t6",
	"MFLO $t7",
	"AND $t8, $t0, $t3",
	"OR $t9, $t0, $t1",
	"XOR $s0, $t0, $t1"
	};

int main()
{
	int i;
	InstructionCode* code;
	FILE* fic=ouvrirFichier("test.as");
	for(i=0;i<decoupe(fic, &code);i++)
	{
		printf("%#010x\n",(unsigned int)code[i]);
	}
	return 0;
}
