#include <stdio.h>
#include "runners.h"
#include "decodeur.c"
#include "instru_util.h"
void runInstruction(Cpu* cpu, u32 instru) {
  ExecContainer ec = Cpu_decode(cpu, (InstructionCode)instru);
  Cpu_exec(cpu, ec);
}

void loadPgrm(RAM* ram, const char* filename) {
	FILE* file = ouvrirFichier(filename);
	
	
	
	
	fermerFichier(file);
}
