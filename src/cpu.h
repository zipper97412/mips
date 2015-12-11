#ifndef CPU_H
#define CPU_H
#include "mem.h"
#include "type.h"
#include "instru_util.h"

typedef struct Regs {
  u32 gpr[32];
  u32 hi;
  u32 lo;
  u32 pc;
} Regs;

Regs Regs_new();
void Regs_display(Regs* self);


typedef struct Cpu {
  MemMap mem;
  Regs regs;
} Cpu;

typedef void (*OperationFunc)(Cpu*, InstructionCode);

typedef struct {
  InstructionCode code;
  OperationFunc func;
}ExecContainer;

Cpu Cpu_new(MemMap mem);
void Cpu_display(Cpu* self);
InstructionCode Cpu_fetch(Cpu* self);
ExecContainer Cpu_decode(Cpu* self, InstructionCode instru);
void Cpu_exec(Cpu* self, ExecContainer container);

void notOp(Cpu* self, InstructionCode mc);

void ADD(Cpu* self, InstructionCode mc);//32
void ADDI(Cpu* self, InstructionCode mc);//8 I
void SUB(Cpu* self, InstructionCode mc);//34
void MULT(Cpu* self, InstructionCode mc);//24
void DIV(Cpu* self, InstructionCode mc);//26

void AND(Cpu* self, InstructionCode mc);//36
void OR(Cpu* self, InstructionCode mc);//37
void XOR(Cpu* self, InstructionCode mc);//38

void SLL(Cpu* self, InstructionCode mc);//0
void SRL(Cpu* self, InstructionCode mc);//2

void SLT(Cpu* self, InstructionCode mc);//42!!!

void LW(Cpu* self, InstructionCode mc);//35 I
void SW(Cpu* self, InstructionCode mc);//43 I
void LUI(Cpu* self, InstructionCode mc);//15 I
void MFHI(Cpu* self, InstructionCode mc);//16
void MHLO(Cpu* self, InstructionCode mc);//18

void BEQ(Cpu* self, InstructionCode mc);//4 I
void BNE(Cpu* self, InstructionCode mc);//5 I
void BGTZ(Cpu* self, InstructionCode mc);//7 I
void BLEZ(Cpu* self, InstructionCode mc);//6 I
void J(Cpu* self, InstructionCode mc);//2 J
void JAL(Cpu* self, InstructionCode mc);//3 J
void JR(Cpu* self, InstructionCode mc);//8

extern OperationFunc opcodeToFuncIJ[64];
extern OperationFunc specialToFuncR[64];


#endif
