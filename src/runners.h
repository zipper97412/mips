#ifndef RUNNERS_H
#define RUNNERS_H
#include "cpu.h"
void runInstruction(Cpu* cpu, u32 instru);
void nonInteractif(const char* filename, int ramsize, int ramOffset, int progOffset, int mode);
void interactif(int ramsize);
void runProg(Cpu* cpu, u32 start, int mode);

#define DEBUG 1
#define NO_DEBUG 0

#endif
