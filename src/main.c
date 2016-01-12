#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodeur.h"

/*const char *tab[]= {
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
	};*/

int main()
{
	int i=0;
	int nbInstru = 0;
	InstructionCode* code =NULL;
	FILE* fic=ouvrirFichier("test.as");
	printf("\"%#010x\"\n", (unsigned int)deterOp("ADD $t2, $t0, $t1").raw);
	code = decoupe(fic, &nbInstru);
	for(i=0;i<nbInstru;i++)
	{
		printf("%#010x\n", (unsigned int)code[i].raw);
	}
	return 0;
}
