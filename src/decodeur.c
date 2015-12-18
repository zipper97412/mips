#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodeur.h"

//MANQUE : J JAL JR LW SW

FILE* ouvrirFichier(char* nom)
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

void decoupe(FILE* fichier)
{
	InstructionCode code;
	int i=0;
	//InstructionType type;
	char tab[28];
	do
	{
		tab[i]=fgetc(fichier);
		i++;
	} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');

	tab[i-1]='\0';

	if(tab[0] != '#') //Si la ligne n'est pas un commentaire
	{
		deterOp(tab, &code, fichier);
	}
	else 
	{
		//On s'en fiche ! La ligne entière est un commentaire.
	}

}

InstructionType deterOp(char* tab, InstructionCode* temp, FILE* fichier)
{
	
	if(strcmp(tab,"ADD") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 32;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"ADDI") == 0)
	{
		int i, j=0;
		temp->op = 8;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		return(Itype);
	}

	else if(strcmp(tab,"AND") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 36;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"BEQ") == 0)
	{
		int i, j=0;
		temp->op = 4;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		return(Itype);
	}

	else if(strcmp(tab,"BGTZ") == 0)
	{
		int i, j=0;
		temp->op = 7;
		temp->rt = 0;
		while(j<2)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		
		return(Itype);
	}

	else if(strcmp(tab,"BLEZ") == 0)
	{
		int i, j=0;
		temp->op = 6;
		temp->rt = 0;
		while(j<2)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		return(Itype);
	}

	else if(strcmp(tab,"BNE") == 0)
	{
		int i, j=0;
		temp->op = 5;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		return(Itype);	
	}

	else if(strcmp(tab,"DIV") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 26;
		temp->sa = 0;
		temp->rd = 0;
		while(j<2)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"J") == 0)
	{
		
		temp->op = 2;
		return(Jtype);
	}

	else if(strcmp(tab,"JAL") == 0)
	{
		temp->op = 3;
		return(Jtype);
	}

	else if(strcmp(tab,"JR") == 0)
	{
		temp->op = 0;
		temp->special = 8;
		temp->sa=0;
		temp->rd=0;
		temp->rt=0;
		return(Rtype);
	}

	else if(strcmp(tab,"LUI") == 0)
	{
		int i, j=0;
		temp->op = 15;
		temp->rs = 0;
		while(j<2)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->immediat=atoi(tab);
			}
			j++;
		}
		return(Itype);
	}

	else if(strcmp(tab,"LW") == 0)
	{
		temp->op = 35;
		return(Itype);
	}

	else if(strcmp(tab,"MFHI") == 0)
	{
		int i=0;
		temp->op = 0;
		temp->special = 16;
		temp->sa = 0;
		temp->rs = 0;
		temp->rt = 0;
		do
		{
			tab[i]=fgetc(fichier);
			i++;
		} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
		tab[0]=tab[i-1];
		i=1;
		do
		{
			tab[i]=fgetc(fichier);
			i++;
		} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
		tab[i-1]='\0';

		temp->rd=convertirRegistre(tab);


		
		return(Rtype);
	}

	else if(strcmp(tab,"MFLO") == 0)
	{
		int i=0;
		temp->op = 0;
		temp->special = 18;
		temp->sa = 0;
		temp->rs = 0;
		temp->rt = 0;
		do
		{
			tab[i]=fgetc(fichier);
			i++;
		} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
		tab[0]=tab[i-1];
		i=1;
		do
		{
			tab[i]=fgetc(fichier);
			i++;
		} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
		tab[i-1]='\0';

		temp->rd=convertirRegistre(tab);

		return(Rtype);
	}

	else if(strcmp(tab,"MULT") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 24;
		temp->sa = 0;
		temp->rd = 0;
		while(j<2)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"OR") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 37;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"ROTR") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 2;
		temp->rs = 1;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->sa=atoi(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"SLL") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 0;
		temp->rs = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->sa=atoi(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"SLT") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 42;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"SRL") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 2;
		temp->rs = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rt=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->sa=atoi(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"SUB") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 34;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else if(strcmp(tab,"SW") == 0)
	{
		temp->op = 43;
		return(Itype);
	}


	else if(strcmp(tab,"XOR") == 0)
	{
		int i, j=0;
		temp->op = 0;
		temp->special = 38;
		temp->sa = 0;
		while(j<3)
		{
			i=0;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] == ' ' || tab[i-1] == ',' || tab[i-1] == '#' || tab[i-1] == EOF || tab[i-1] == '\n');
			tab[0]=tab[i-1];
			i=1;
			do
			{
				tab[i]=fgetc(fichier);
				i++;
			} while(tab[i-1] != ' ' || tab[i-1] != ',' || tab[i-1] != '#' || tab[i-1] != EOF || tab[i-1] != '\n');
			tab[i-1]='\0';
			if(j==0)
			{
				temp->rd=convertirRegistre(tab);
			}
			else if (j==1)
			{
				temp->rs=convertirRegistre(tab);
			}
			else if (j==2)
			{
				temp->rt=convertirRegistre(tab);
			}
			j++;
		}
		return(Rtype);
	}

	else
	{
		printf("Mauvaise instruction ! \n");
		exit(1);
	}
}

/*int convertirRegistre(char* tab)
{

}*/
