#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodeur.h"

int main()
{
	InstructionCode* code;
	FILE* fic=ouvrirFichier("test.as");
	for(i=0;i<decoupe(fic, &code);i++)
	{
		printf("%#010x\n", code[i]);
	}
	return 0;
}
