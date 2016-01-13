#include <stdio.h>
#include "runners.h"
#include "decodeur.c"
#include "instru_util.h"
void runInstruction(Cpu* cpu, u32 instru) {
  ExecContainer ec = Cpu_decode(cpu, (InstructionCode)instru);
  Cpu_exec(cpu, ec);
}

int loadPgrm(RAM* ram, const char* filename) {
  int nbInstru = 0;
	InstructionCode* code =NULL;
	FILE* file=ouvrirFichier(filename);
	code = decoupe(file, &nbInstru);
  u8* ramTab = NULL;
  ramTab = malloc(nbInstru*4*sizeof(u8));
  if(ramTab == NULL) {
    fprintf(stderr, "erreur malloc\n");
    exit(0);
  }
  ram->data = ramTab;
  ram->len = nbInstru*4;
  printf("%d\n", nbInstru);
  int i;
  for(i=0;i<nbInstru;i++) {
    RAM_write_word(ram, i*4, code[i].raw);
  }
	fermerFichier(file);
  return nbInstru;
}

void interactif(int ramsize) {
  u8* ramTab = NULL;
  u8* progTab = NULL;
  ramTab = malloc(ramsize*sizeof(u8));
  if(ramTab == NULL) {
    fprintf(stderr, "erreur malloc\n");
    exit(0);
  }
  RAM ram = RAM_new(ramTab, ramsize);
  RAM prog = RAM_new(progTab, 0);
  MemMap memMap = MemMap_new(&ram, 0, ramsize, &prog, 0, 0);
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
void nonInteractif(const char* filename, int ramsize, int ramOffset) {
  u8* ramTab = NULL;
  ramTab = malloc(ramsize*sizeof(u8));
  if(ramTab == NULL) {
    fprintf(stderr, "erreur malloc\n");
    exit(0);
  }
  RAM ram = RAM_new(ramTab, ramsize);
  RAM prog;
  int nbInstru = loadPgrm(&prog, filename);
  MemMap memMap = MemMap_new(&ram,ramOffset, ramsize, &prog, 0, nbInstru*4);
  Cpu cpu = Cpu_new(memMap);
  printf("--------------------execution----------------\n");
  Cpu_display(&cpu);
  runProg(&cpu, 0);
  //Cpu_display(&cpu);

}
void runProg(Cpu* cpu, u32 start) {
  u32 instruction = 0;
  ExecContainer ec;
  cpu->regs.pc = start;
  while(instruction != 0xffeeffee) {
    instruction = Cpu_fetch(cpu).raw;
    ec = Cpu_decode(cpu, (InstructionCode)instruction);
    Cpu_exec(cpu, ec);
  }
}
