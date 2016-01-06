#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodeur.h"

int main()
{
	InstructionCode code;
	char tab[50]="ADDI $t0, $zero, 5";
	printf("%#010x\n", (unsigned int)deterOp(tab, &code).raw);
	return 0;
}
