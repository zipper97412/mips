
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "runners.h"

void usage() {
  
  fprintf(stderr, "usage: ./mips -r ramsize -o ramoffset [-e fichier [-p]]\n");
	fprintf(stderr, "\
-r ramsize: taille mémoire de donnée (obligatoire)\n\
-o ramoffset: emplacement premier octet de la ram (faire attention aux collisions avec la mémoire de programme\
qui commence à 0 et dont la taille dépend du nombre d'instructions dans le fichier source)(obligatoire)\n\
-e fichier: nom du fichier source contenant du code assembleur mips (mode interactif si non précisé)\n\
-p : mode pas à pas dans le cas d'un fichier chargé\n\
	");
  exit(1);
}

int main(int argc, char* argv[]) {
	char c;
	extern char * optarg;
	int ficflag=0,ramflag=0,offsetflag=0;
	char* fichier = NULL;
	int ramsize=0;
	int ramoffset=0;
	int pap=NO_DEBUG;
	while ((c = getopt(argc , argv, "po:r:e:")) != -1) {
		switch (c) {
    case 'e':
			fichier = optarg;
      printf("fichier choisis: %s\nmode ecexution\n", fichier);
			ficflag++;
      break;
    case 'p':
      printf("mode pas a pas\n");
			pap = DEBUG;
      break;
    case 'r':
			ramsize = atoi(optarg);
      printf("%d octets de mémoire de donnée\n",ramsize);
			ramflag++;
      break;
		case 'o':
			ramoffset = atoi(optarg);
      printf("mémoire de donnée située à %#010x\n",(unsigned int)ramoffset);
			offsetflag++;
      break;
    case '?':
      usage();
      break;
    }
	}
	if((ramflag == 1) && (offsetflag == 1)) {
		if(ficflag == 1) {
			nonInteractif(fichier, ramsize, ramoffset, 0, pap);
		}
		else {
			interactif(ramsize, ramoffset);
		}
	}
	else {
		usage();
	} 
	/*u8 ramTab[1024];
  RAM ram = RAM_new(ramTab,1024);
  MemMap memmap = MemMap_new(&ram, 42, 42+1024,);
  Cpu cpu = Cpu_new(memmap);
  Cpu_display(&cpu);
  printf("memtest word:\n");
  printf("ecriture:\n");
  MemMap_write_word(&memmap, 42+1020, 0x11223344);
  MemMap_display(&memmap);
  printf("lecture:\n");
  printf("%#010x\n",(unsigned int)MemMap_read_word(&memmap, 42+1020));
  InstructionCode ins;
  ins.raw = 0x4210841;
  int ok = 0;
  ok += (ins.raw == 0x4210841);
  ok += (ins.special == 1);
  ok += (ins.sa == 1);
  ok += (ins.rd == 1);
  ok += (ins.rt == 1);
  ok += (ins.rs == 1);
  ok += (ins.op == 1);
  ok += (ins.immediat == 0x841);
  ok += (ins.target == 0x210841);
  printf("test lecture champ d'instruction:\nun 9 doit apparaitre ici:%d\n", ok);
  ins.immediat = 1;
  ok = 0;
  ok += (ins.raw == 0x4210001);
  ins.target = 1;
  ok += (ins.raw == 0x4000001);
  printf("test ecriture champ insruction:\nun 2 doit apparaitre ici:%d\n", ok);
  */
  //interactif(128);
  //nonInteractif("test_fic", 128, 1024, 0, DEBUG);



  return 0;
}
