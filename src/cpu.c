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
  printf("\nCpu Registers:\n");
	printf("$zero ($0): %#010x\t\t",(unsigned int)self->gpr[0]);
	printf("$at ($1):  %#010x\t\t",(unsigned int)self->gpr[1]);
	printf("$v0 ($2):  %#010x\t\t",(unsigned int)self->gpr[2]);
	printf("$a0 ($4):  %#010x",(unsigned int)self->gpr[4]);
	printf("\n\t\t\t\t\t\t\t\t$v1 ($3):  %#010x",(unsigned int)self->gpr[3]);
	printf("\t\t$a1 ($5):  %#010x\n",(unsigned int)self->gpr[5]);
	printf("$t0 ($8):  %#010x\t\t",(unsigned int)self->gpr[8]);
	printf("$s0 ($16): %#010x\t\t",(unsigned int)self->gpr[16]);
	printf("\t\t\t\t$a2 ($6):  %#010x\n",(unsigned int)self->gpr[6]);
	printf("$t1 ($9):  %#010x\t\t",(unsigned int)self->gpr[9]);
	printf("$s1 ($17): %#010x\t\t",(unsigned int)self->gpr[17]);
	printf("$k0 ($26): %#010x",(unsigned int)self->gpr[26]);
	printf("\t\t$a3 ($7):  %#010x\n",(unsigned int)self->gpr[7]);
	printf("$t2 ($10): %#010x\t\t",(unsigned int)self->gpr[10]);
	printf("$s2 ($18): %#010x\t\t",(unsigned int)self->gpr[18]);
	printf("$k1 ($27): %#010x\n",(unsigned int)self->gpr[27]);
	printf("$t3 ($11): %#010x\t\t",(unsigned int)self->gpr[11]);
	printf("$s3 ($19): %#010x\t\t\t\t",(unsigned int)self->gpr[19]);
	printf("\t\t$gp ($28): %#010x\n",(unsigned int)self->gpr[28]);
	printf("$t4 ($12): %#010x\t\t",(unsigned int)self->gpr[12]);
	printf("$s4 ($20): %#010x\t\t",(unsigned int)self->gpr[20]);
	printf("$sp ($29): %#010x",(unsigned int)self->gpr[29]);
	printf("\t\t$fp ($30): %#010x\n",(unsigned int)self->gpr[30]);
	printf("$t5 ($13): %#010x\t\t",(unsigned int)self->gpr[13]);
	printf("$s5 ($21): %#010x\t\t",(unsigned int)self->gpr[21]);
	printf("$ra ($31): %#010x\n",(unsigned int)self->gpr[31]);
	printf("$t6 ($14): %#010x\t\t",(unsigned int)self->gpr[14]);
	printf("$s6 ($22): %#010x\t\t",(unsigned int)self->gpr[22]);
	printf("\t\t\t\t$HI: %#010x\n",(unsigned int)self->hi);
	printf("$t7 ($15): %#010x\t\t",(unsigned int)self->gpr[15]);
	printf("$s7 ($23): %#010x\t\t",(unsigned int)self->gpr[23]);
	printf("$pc: %#010x\t",(unsigned int)self->pc);
	printf("\t\t$LO: %#010x\n",(unsigned int)self->lo);
	printf("$t8 ($24): %#010x\t\t\n",(unsigned int)self->gpr[24]);
	printf("$t9 ($25): %#010x\t\t\n\n",(unsigned int)self->gpr[25]);
}
Cpu Cpu_new(MemMap mem) {
  Cpu cpu;
  cpu.mem = mem;
  cpu.regs = Regs_new();
  return cpu;
}
void Cpu_display(Cpu* self) {
  //Regs_display(&self->regs);
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
