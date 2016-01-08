#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "instru_util.h"
#include "decodeur.h"

//MANQUE : J JAL JR LW SW

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

int decoupe(FILE* fichier, InstructionCode** pgrm)
{
	*pgrm = NULL;
	int pgrmLen = 0;
	int i,e=0;
	//InstructionType type;
	char tableau[28];
	do
	{
		i=0;
		do
		{
			tableau[i]=fgetc(fichier);
			i++;
		} while(tableau[i-1] != '#' || tableau[i-1] != EOF || tableau[i-1] != '\n');
		if(tableau[i-1]==EOF)
		{
			e=1;
		}
		if(tableau[i-1]=='#')
		{
			while(fgetc(fichier)!='\n');
		}
		tableau[i-1]='\0';

		if(tableau[0] != '#') //Si la ligne n'est pas un commentaire
		{
			*pgrm = realloc(*pgrm,sizeof(InstructionCode)*++pgrmLen);
			*pgrm[pgrmLen] = deterOp(tableau);
		}
		else
		{
			//On s'en fiche ! La ligne entière est un commentaire.
		}
	}while(e==0);
	return pgrmLen;
}

InstructionCode deterOp(char* tableau)
{
	int i=0,j=0,k=0;
	char tab[10];
	InstructionCode temp;
	do
	{
		tab[i]=tableau[i];
		i++;
	} while(tableau[i-1] != ' ');
	tab[i-1]='\0';

	if(strcmp(tab,"ADD") == 0)
	{
		temp.op = 0;
		temp.special = 32;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"ADDI") == 0)
	{
		temp.op = 8;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;

			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"AND") == 0)
	{
		temp.op = 0;
		temp.special = 36;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';
			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"BEQ") == 0)
	{
		temp.op = 4;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"BGTZ") == 0)
	{
		temp.op = 7;
		temp.rt = 0;
		while(k<2)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';
			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"BLEZ") == 0)
	{
		temp.op = 6;
		temp.rt = 0;
		while(k<2)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"BNE") == 0)
	{
		temp.op = 5;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"DIV") == 0)
	{
		temp.op = 0;
		temp.special = 26;
		temp.sa = 0;
		temp.rd = 0;
		while(k<2)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"J") == 0)
	{
		temp.op = 2;
	}

	else if(strcmp(tab,"JAL") == 0)
	{
		temp.op = 3;
	}

	else if(strcmp(tab,"JR") == 0)
	{
		temp.op = 0;
		temp.special = 8;
		temp.sa=0;
		temp.rd=0;
		temp.rt=0;
	}

	else if(strcmp(tab,"LUI") == 0)
	{
		temp.op = 15;
		temp.rs = 0;
		while(k<2)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.immediat=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"LW") == 0)
	{
		temp.op = 35;
	}

	else if(strcmp(tab,"MFHI") == 0)
	{
		temp.op = 0;
		temp.special = 16;
		temp.sa = 0;
		temp.rs = 0;
		temp.rt = 0;

		while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
		{
			i++;
		}
		do
		{
			tab[j]=tableau[i];
			i++;
			j++;
		} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
		tab[j]='\0';
		temp.rd=convertirRegistre(tab);
	}

	else if(strcmp(tab,"MFLO") == 0)
	{
		temp.op = 0;
		temp.special = 18;
		temp.sa = 0;
		temp.rs = 0;
		temp.rt = 0;
		while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
		{
			i++;
		}
		do
		{
			tab[j]=tableau[i];
			i++;
			j++;
		} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
		tab[j]='\0';
		temp.rd=convertirRegistre(tab);
	}

	else if(strcmp(tab,"MULT") == 0)
	{
		temp.op = 0;
		temp.special = 24;
		temp.sa = 0;
		temp.rd = 0;
		while(k<2)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"OR") == 0)
	{
		temp.op = 0;
		temp.special = 37;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"ROTR") == 0)
	{
		temp.op = 0;
		temp.special = 2;
		temp.rs = 1;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.sa=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"SLL") == 0)
	{
		temp.op = 0;
		temp.special = 0;
		temp.rs = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.sa=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"SLT") == 0)
	{
		temp.op = 0;
		temp.special = 42;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"SRL") == 0)
	{
		temp.op = 0;
		temp.special = 2;
		temp.rs = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rt=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.sa=atoi(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"SUB") == 0)
	{
		temp.op = 0;
		temp.special = 34;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else if(strcmp(tab,"SW") == 0)
	{
		temp.op = 43;
	}


	else if(strcmp(tab,"XOR") == 0)
	{
		temp.op = 0;
		temp.special = 38;
		temp.sa = 0;
		while(k<3)
		{
			j=0;
			while(tableau[i] == ' ' || tableau[i] == '$' || tableau[i] == ',')
			{
				i++;
			}
			do
			{
				tab[j]=tableau[i];
				i++;
				j++;
			} while((tableau[i] != ' ') && (tableau[i] != ',') && (tableau[i] != '#') && (tableau[i] != EOF) && 				(tableau[i] != '\n'));
			tab[j]='\0';

			if(k==0)
			{
				temp.rd=convertirRegistre(tab);
			}
			else if (k==1)
			{
				temp.rs=convertirRegistre(tab);
			}
			else if (k==2)
			{
				temp.rt=convertirRegistre(tab);
			}
			k++;
		}
	}

	else
	{
		printf("Mauvaise instruction ! \n");
		exit(1);
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
