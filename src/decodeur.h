#ifndef DECODEUR_H
#define DECODEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "instru_util.h"


FILE* ouvrirFichier(char* nom);
void fermerFichier(FILE* fichier);
InstructionCode* decoupe(FILE* fichier);
InstructionCode deterOp(char* tab);
int convertirRegistre(char* tab);

#endif
