#include "cpu.h"

void notOp(Cpu* self, InstructionCode mc) {}
void RtypeDispatcher(Cpu* self, InstructionCode mc) {
  specialToFuncR[mc.special](self, mc);
}

void ADD(Cpu* self, InstructionCode mc) {}//32
void ADDI(Cpu* self, InstructionCode mc) {}//8 I
void SUB(Cpu* self, InstructionCode mc) {}//34
void MULT(Cpu* self, InstructionCode mc) {}//24
void DIV(Cpu* self, InstructionCode mc) {}//26

void AND(Cpu* self, InstructionCode mc) {}//36
void OR(Cpu* self, InstructionCode mc) {}//37
void XOR(Cpu* self, InstructionCode mc) {}//38

void SLL(Cpu* self, InstructionCode mc) {}//0
void SRL(Cpu* self, InstructionCode mc) {}//2

void SLT(Cpu* self, InstructionCode mc) {}//42!!!

void LW(Cpu* self, InstructionCode mc) {}//35 I
void SW(Cpu* self, InstructionCode mc) {}//43 I
void LUI(Cpu* self, InstructionCode mc) {}//15 I
void MFHI(Cpu* self, InstructionCode mc) {}//16
void MHLO(Cpu* self, InstructionCode mc) {}//18

void BEQ(Cpu* self, InstructionCode mc) {}//4 I
void BNE(Cpu* self, InstructionCode mc) {}//5 I
void BGTZ(Cpu* self, InstructionCode mc) {}//7 I
void BLEZ(Cpu* self, InstructionCode mc) {}//6 I
void J(Cpu* self, InstructionCode mc) {}//2 J
void JAL(Cpu* self, InstructionCode mc) {}//3 J
void JR(Cpu* self, InstructionCode mc) {}//8

OperationFunc opcodeToFuncIJ[64] = {
  &RtypeDispatcher,
  &notOp,
  &J,
  &JAL,
  &BEQ,
  &BNE,
  &BLEZ,
  &BGTZ,
  &ADDI,
  [9 ... 14] = &notOp,
  &LUI,
  [16 ... 34] = &notOp,
  &LW,
  [36 ... 42] = &notOp,
  &SW,
  [44 ... 63] = &notOp
};
OperationFunc specialToFuncR[64] = {
  &SLL,
  &notOp,
  &SRL,
  [3 ... 7] = &notOp,
  &JR,
  [9 ... 15] = &notOp,
  &MFHI,
  &notOp,
  &MHLO,
  [19 ... 23] = &notOp,
  &MULT,
  &notOp,
  &DIV,
  [27 ... 31] = &notOp,
  &ADD,
  &notOp,
  &SUB,
  &notOp,
  &AND,
  &OR,
  &XOR,
  [39 ... 41] = &notOp,
  &SLT,
  [43 ... 63] = &notOp,
};
