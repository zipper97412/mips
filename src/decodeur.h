#ifndef DECODEUR_H
#define DECODEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "instru_util.h"
typedef enum 
{
	Rtype,
	Itype,
	Jtype
} InstructionType;


FILE* ouvrirFichier(char* nom);
void fermerFichier(FILE* fichier);
void decoupe(FILE* fichier);
InstructionType deterOp(char* tab, InstructionCode* temp);
int convertirRegistre(char* tab);

#endif
