#ifndef CPU_H
#define CPU_H
#include "mem.h"
#include "type.h"

typedef struct Regs {
  u32 gpr[32];
  u32 hi;
  u32 lo;
} Regs;
Regs Regs_new();
void Regs_display(Regs* self);


typedef struct Cpu {
  MemMap mem;
  Regs regs;
} Cpu;
Cpu Cpu_new(MemMap mem);
void Cpu_step(Cpu* self);
void Cpu_setInstruction(Cpu* self, u32 instruction);
void Cpu_display(Cpu* self);

#endif
