#include "cpu.h"
#include <stdio.h>



Regs Regs_new() {
	int i=0;
  Regs regs;
  regs.pc = 0;
  for(i=0;i<32;i++) {
    regs.gpr[i]=(u32)0;
  }
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
  printf("$pc:\t\t%#010x\n",(unsigned int)self->pc);
}

Cpu Cpu_new(MemMap mem) {
  Cpu cpu;
  cpu.mem = mem;
  cpu.regs = Regs_new();
  return cpu;
}
void Cpu_display(Cpu* self) {
  Regs_display(&self->regs);
  MemMap_display(&self->mem);
}

InstructionCode Cpu_fetch(Cpu* self) {
  u32 instru = MemMap_read_word(&self->mem, self->regs.pc);
  self->regs.pc += 4;
  return (InstructionCode)instru;
}
ExecContainer Cpu_decode(Cpu* self, InstructionCode instru) {
  ExecContainer ec = {
    code: instru,
    func: opcodeToFuncIJ[instru.op]
  };
  return ec;
}

void Cpu_exec(Cpu* self, ExecContainer container) {
  container.func(self, container.code);
}
