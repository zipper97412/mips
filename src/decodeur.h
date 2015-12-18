typedef enum 
{
	Rtype,
	Itype,
	Jtype
} InstructionType;


FILE* ouvrirFichier(char* nom);
void fermerFichier(FILE* fichier);
void decoupe(FILE* fichier);
InstructionType deterOp(char* tab, InstructionCode* temp, FILE* fichier);
//int convertirRegistre(char* tab);
