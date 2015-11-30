#include "cpu.h"
#include <stdio.h>

Regs Regs_new() {
  Regs regs;
  return regs;
}
void Regs_display(Regs* self) {
  int i;
  printf("\nCpu Registers:\n");
  for(i=0;i<32;i++) {
    if( i == 0 ) printf("$zero");
    if( i == 1 ) printf("$at");
    if( i == 2 ) printf("$v0,$v1");
    if( i == 4 ) printf("$a0-$a3");
    if( i == 8 ) printf("$t0-$t7");
    if( i == 16 ) printf("$s0-$s7");
    if( i == 24 ) printf("$t8,$t9");
    if( i == 26 ) printf("$k0,$k1");
    if( i == 28 ) printf("$gp");
    if( i == 29 ) printf("$sp");
    if( i == 30 ) printf("$fp");
    if( i == 31 ) printf("$ra");
    printf("\t\t");
    printf(" ($%d):    \t",i);
    printf("%#010x\n",(unsigned int)self->gpr[i]);

  }
  printf("$HI,$LO:\t\t%#010x %#010x\n",(unsigned int)self->hi,(unsigned int)self->lo);
}

Cpu Cpu_new(MemMap mem) {
  Cpu cpu;
  cpu.mem = mem;
  cpu.regs = Regs_new();
  return cpu;
}
void Cpu_step(Cpu* self) {

}
void Cpu_setInstruction(Cpu* self, u32 instruction) {

}
void Cpu_display(Cpu* self) {
  Regs_display(&self->regs);
  MemMap_display(&self->mem);
}
