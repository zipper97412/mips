#ifndef RUNNERS_H
#define RUNNERS_H
#include "cpu.h"
void runInstruction(Cpu* cpu, u32 instru);
void runProg(Cpu* cpu, u32 firstInstru);

#endif
