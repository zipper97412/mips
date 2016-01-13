#ifndef RUNNERS_H
#define RUNNERS_H
#include "cpu.h"
void runInstruction(Cpu* cpu, u32 instru);
void nonInteractif(const char* filename, int ramsize, int ramOffset);
void interactif(int ramsize);
void runProg(Cpu* cpu, u32 start);

#endif
