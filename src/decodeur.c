#include "decodeur.h"

//MANQUE : J JAL JR LW SW

/* Fonction permettant d'ouvrir les fichiers et de gérer les possibles erreurs */
FILE* ouvrirFichier(const char* nom)
{
	FILE* fichierTest = fopen(nom, "r+");
	if (fichierTest == NULL)
	{
		perror("Problème lors de l'ouverture du fichier\n");
		exit(1);
	}
	return (fichierTest);
}

void fermerFichier(FILE* fichier)
{
	fclose(fichier);
}

/*int isIn(char c, const char* delim, int nbelem) {
	for(int i=0;i<nbelem;i++) {
		if(c == delim[i])
			return 1;
	}
	return 0;
}*/
/* Fonction lisant un fichier, et remplissant un tableau avec le contenu du fichier*/
InstructionCode* decoupe(FILE* fichier, int* pgrmLen)
{
	InstructionCode* pgrm = NULL;
	int nbInstruction = 0;
	int i, job = 1;
	char tableau[100];
	char c;

	while(job)
	{
		i=0;
		//char delimiter[] = {'#','\n'};
		while( ((c=fgetc(fichier)) != EOF ) && (c != '#') && (c != '\n') )
		{
			tableau[i]=c;
			i++;
		}
		tableau[i]='\0';//Ne pas oublier de terminer le tableau.

		if(c==EOF) //Si nous sommes arrivés à la fin du fichier, nous sortons de cette fonction
			job = 0;
		else if(c=='#')//Si le dernier caractère lu est un commentaire, nous lisons l'intégralité de la ligne pour passer à la ligne suivante
			while(fgetc(fichier)!='\n');
		else {
			printf("\"%s\"\n", tableau);
			nbInstruction++;
			pgrm = realloc(pgrm, nbInstruction*sizeof(InstructionCode));
			if( (pgrm[nbInstruction-1] = deterOp(tableau)).raw == 0xffffffff ) {
				exit(0);
			}

			//printf("\"%#010x\"\n", (unsigned int)deterOp(tableau).raw);
		}

	} //Boucle tant que nous ne sommes pas arrivés à la fin du fichier

	*pgrmLen = nbInstruction;
	return pgrm;
}


void nextLex(char* outBuffer, char* inBuffer, int* index) {

	int j=0;
	//char delimiter[] = {' ','$',',','#','\n','(',')'};
	//char errordelimiter[] = {'\n','#'};

	while( 	(inBuffer[*index] == ' ') ||
					(inBuffer[*index] == '$') ||
					(inBuffer[*index] == ',') ||
					(inBuffer[*index] == '#') ||
					(inBuffer[*index] == ';') ||
					(inBuffer[*index] == '\n') ||
					(inBuffer[*index] == '(') ||
					(inBuffer[*index] == ')'))
	{
		if( (inBuffer[*index] == '#') || (inBuffer[*index] == '\n')) {
			fprintf(stderr, "erreur de parseur\n");
			exit(0);
		}
		*index += 1;
	}
	while(	(inBuffer[*index] != ' ') &&
					(inBuffer[*index] != '$') &&
					(inBuffer[*index] != ',') &&
					(inBuffer[*index] != '#') &&
					(inBuffer[*index] != ';') &&
					(inBuffer[*index] != '\n') &&
					(inBuffer[*index] != '(') &&
					(inBuffer[*index] != ')') &&
					(inBuffer[*index] != EOF))
	{
		outBuffer[j]=inBuffer[*index];
		*index += 1;
		j++;
	}
	outBuffer[j]='\0';//Ne pas oublier de terminer le tableau.
}

/*Fonction permettant de remplir l'union de structure*/
InstructionCode deterOp(char* tableau)
{
	int i=0;
	char tab[50];
	InstructionCode temp;
	nextLex(tab, tableau, &i);

/*Nous réalisons alors beaucoup de cas pour trouver quelle est l'instruction*/
/*Nous remplissons alors les différents champs (op, rs, rt, etc...) en fonction de l'instruction*/

	if(strcmp(tab,"ADD") == 0)
	{
		/* Remplissage des champs*/
		temp.op = 0;
		temp.special = 32;
		temp.sa = 0;
		nextLex(tab, tableau, &i);
		temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
	}

	/*Raisonnement similaire pour toutes les instruction*/

	else if(strcmp(tab,"ADDI") == 0)
	{
		temp.op = 8;
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.immediat=atoi(tab);

	}

	else if(strcmp(tab,"AND") == 0)
	{
		temp.op = 0;
		temp.special = 36;
		temp.sa = 0;
		nextLex(tab, tableau, &i);
		temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
	}

	else if(strcmp(tab,"BEQ") == 0)
	{
		temp.op = 4;
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.immediat=atoi(tab);

	}

	else if(strcmp(tab,"BGTZ") == 0)
	{
		temp.op = 7;
		temp.rt = 0;
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.immediat=atoi(tab);

	}

	else if(strcmp(tab,"BLEZ") == 0)
	{
		temp.op = 6;
		temp.rt = 0;
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
		temp.immediat=atoi(tab);

	}

	else if(strcmp(tab,"BNE") == 0)
	{
		temp.op = 5;
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.immediat=atoi(tab);

	}

	else if(strcmp(tab,"DIV") == 0)
	{
		temp.op = 0;
		temp.special = 26;
		temp.sa = 0;
		temp.rd = 0;
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);

	}

	else if(strcmp(tab,"J") == 0)
	{
		temp.op = 2;
		nextLex(tab, tableau, &i);
		temp.target=atoi(tab);
	}

	else if(strcmp(tab,"JAL") == 0)
	{
		temp.op = 3;
		nextLex(tab, tableau, &i);
		temp.target=atoi(tab);
	}

	else if(strcmp(tab,"JR") == 0)
	{
		temp.op = 0;
		temp.special = 8;
		temp.sa=0;
		temp.rd=0;
		temp.rt=0;
		nextLex(tab, tableau, &i);
		temp.rs=convertirRegistre(tab);

	}

	else if(strcmp(tab,"LUI") == 0)
	{
		temp.op = 15;
		temp.rs = 0;
		nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.immediat=atoi(tab);
	}

	else if(strcmp(tab,"LW") == 0)
	{
		temp.op = 35;
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.immediat=atoi(tab);
		nextLex(tab, tableau, &i);
				temp.rs=atoi(tab);
	}

	else if(strcmp(tab,"MFHI") == 0)
	{
		temp.op = 0;
		temp.special = 16;
		temp.sa = 0;
		temp.rs = 0;
		temp.rt = 0;
		nextLex(tab, tableau, &i);
		temp.rd=convertirRegistre(tab);
	}

	else if(strcmp(tab,"MFLO") == 0)
	{
		temp.op = 0;
		temp.special = 18;
		temp.sa = 0;
		temp.rs = 0;
		temp.rt = 0;
		nextLex(tab, tableau, &i);
		temp.rd=convertirRegistre(tab);
	}

	else if(strcmp(tab,"MULT") == 0)
	{
		temp.op = 0;
		temp.special = 24;
		temp.sa = 0;
		temp.rd = 0;
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
	}

	else if(strcmp(tab,"OR") == 0)
	{
		temp.op = 0;
		temp.special = 37;
		temp.sa = 0;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
	}

	else if(strcmp(tab,"ROTR") == 0)
	{
		temp.op = 0;
		temp.special = 2;
		temp.rs = 1;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.sa=atoi(tab);
	}

	else if(strcmp(tab,"SLL") == 0)
	{
		temp.op = 0;
		temp.special = 0;
		temp.rs = 0;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.sa=atoi(tab);
	}

	else if(strcmp(tab,"SLT") == 0)
	{
		temp.op = 0;
		temp.special = 42;
		temp.sa = 0;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
	}

	else if(strcmp(tab,"SRL") == 0)
	{
		temp.op = 0;
		temp.special = 2;
		temp.rs = 0;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.sa=atoi(tab);
	}

	else if(strcmp(tab,"SUB") == 0)
	{
		temp.op = 0;
		temp.special = 34;
		temp.sa = 0;
	nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
	}

	else if(strcmp(tab,"SW") == 0)
	{
		temp.op = 43;
		nextLex(tab, tableau, &i);
		temp.rt=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.immediat=atoi(tab);
			nextLex(tab, tableau, &i);
				temp.rs=atoi(tab);
	}


	else if(strcmp(tab,"XOR") == 0)
	{
		temp.op = 0;
		temp.special = 38;
		temp.sa = 0;
		nextLex(tab, tableau, &i);
				temp.rd=convertirRegistre(tab);
		nextLex(tab, tableau, &i);
				temp.rs=convertirRegistre(tab);
			nextLex(tab, tableau, &i);
				temp.rt=convertirRegistre(tab);
	}
	else if(strcmp(tab,"HALT") == 0)
	{
		temp.raw = 0xffeeffee;
	}

	else
	{
		fprintf(stderr,"Mauvaise instruction ! %s\n", tab);
		temp.raw = 0xffffffff;
	}
	return temp;
}

int convertirRegistre(char* tab)
{
	if(strcmp(tab,"zero") == 0)
	{
		return 0;
	}

	else if(strcmp(tab,"at") == 0)
	{
		return 1;
	}

	else if(strcmp(tab,"v0") == 0)
	{
		return 2;
	}

	else if(strcmp(tab,"v1") == 0)
	{
		return 3;
	}

	else if(strcmp(tab,"a0") == 0)
	{
		return 4;
	}

	else if(strcmp(tab,"a1") == 0)
	{
		return 5;
	}

	else if(strcmp(tab,"a2") == 0)
	{
		return 6;
	}

	else if(strcmp(tab,"a3") == 0)
	{
		return 7;
	}

	else if(strcmp(tab,"t0") == 0)
	{
		return 8;
	}

	else if(strcmp(tab,"t1") == 0)
	{
		return 9;
	}

	else if(strcmp(tab,"t2") == 0)
	{
		return 10;
	}

	else if(strcmp(tab,"t3") == 0)
	{
		return 11;
	}

	else if(strcmp(tab,"t4") == 0)
	{
		return 12;
	}

	else if(strcmp(tab,"t5") == 0)
	{
		return 13;
	}

	else if(strcmp(tab,"t6") == 0)
	{
		return 14;
	}

	else if(strcmp(tab,"t7") == 0)
	{
		return 15;
	}

	else if(strcmp(tab,"s0") == 0)
	{
		return 16;
	}

	else if(strcmp(tab,"s1") == 0)
	{
		return 17;
	}

	else if(strcmp(tab,"s2") == 0)
	{
		return 18;
	}

	else if(strcmp(tab,"s3") == 0)
	{
		return 19;
	}

	else if(strcmp(tab,"s4") == 0)
	{
		return 20;
	}

	else if(strcmp(tab,"s5") == 0)
	{
		return 21;
	}

	else if(strcmp(tab,"s6") == 0)
	{
		return 22;
	}

	else if(strcmp(tab,"s7") == 0)
	{
		return 23;
	}

	else if(strcmp(tab,"t8") == 0)
	{
		return 24;
	}

	else if(strcmp(tab,"t9") == 0)
	{
		return 25;
	}

	else if(strcmp(tab,"k0") == 0)
	{
		return 26;
	}

	else if(strcmp(tab,"k1") == 0)
	{
		return 27;
	}

	else if(strcmp(tab,"gp") == 0)
	{
		return 28;
	}

	else if(strcmp(tab,"sp") == 0)
	{
		return 29;
	}

	else if(strcmp(tab,"fp") == 0)
	{
		return 30;
	}

	else if(strcmp(tab,"ra") == 0)
	{
		return 31;
	}

	else
	{
		return atoi(tab);
	}
}
