#include <stdio.h>
#include "runners.h"
#include "decodeur.c"
#include "instru_util.h"
void runInstruction(Cpu* cpu, u32 instru) {
  ExecContainer ec = Cpu_decode(cpu, (InstructionCode)instru);
  Cpu_exec(cpu, ec);
}

void loadPgrm(RAM* ram, const char* filename) {
  int nbInstru = 0;
	InstructionCode* code =NULL;
	FILE* fic=ouvrirFichier(filename);
	code = decoupe(fic, &nbInstru);
  //----------------------pas fini---------------------
	fermerFichier(file);
}

void interactif() {
  u8 ramTab[128];
  RAM ram = RAM_new(ramTab, 128);
  MemMap memMap = MemMap_new(&ram, 0, 128);
  Cpu cpu = Cpu_new(memMap);
  char buffer[100];
  u32 instruction;
  printf("--------------------execution----------------\n");
  printf("mode interactif, quit pour quiter mem pour afficher la memoire \n");
  Cpu_display(&cpu);
  while(1) {
    Regs_display(&cpu.regs);
    //scanf("%s", buffer);
    fgets(buffer, 100, stdin);
    fflush(stdin);
    if(strcmp(buffer,"quit\n")==0)
      break;
    if(strcmp(buffer,"ram\n")==0)
      MemMap_display(&memMap);
    instruction = deterOp(buffer).raw;
    if (instruction == 0) {

    }
    else {
      printf("code machine: %#010x\n", (unsigned int)instruction);
      runInstruction(&cpu, instruction);
    }
  }

}
