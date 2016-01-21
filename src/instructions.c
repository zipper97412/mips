#include "cpu.h"
#include "type.h"

void notOp(Cpu* self, InstructionCode mc) {}
void RtypeDispatcher(Cpu* self, InstructionCode mc) {
  specialToFuncR[mc.special](self, mc);
}

void ADD(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = (i32)(self->regs.gpr[mc.rs]) + (i32)(self->regs.gpr[mc.rt]);
}//32
void ADDI(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rt] = (i32)(self->regs.gpr[mc.rs]) + (i32)(mc.immediat);
}//8 I
void SUB(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = (i32)(self->regs.gpr[mc.rs]) - (i32)(self->regs.gpr[mc.rt]);
}//34
void MULT(Cpu* self, InstructionCode mc) {
	u64hilo temp = (u64hilo)( (i64)(self->regs.gpr[mc.rs]) * (i64)(self->regs.gpr[mc.rt]) );
	self->regs.hi = temp.hi;
	self->regs.lo = temp.lo;
}//24
void DIV(Cpu* self, InstructionCode mc) {
	self->regs.lo = (i32)(self->regs.gpr[mc.rs]) / (i32)(self->regs.gpr[mc.rt]);
	self->regs.hi = (i32)(self->regs.gpr[mc.rs]) % (i32)(self->regs.gpr[mc.rt]);
}//26

void AND(Cpu* self, InstructionCode mc) { 
	self->regs.gpr[mc.rd] = self->regs.gpr[mc.rs] & self->regs.gpr[mc.rt];
}//36
void OR(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = self->regs.gpr[mc.rs] | self->regs.gpr[mc.rt];
}//37
void XOR(Cpu* self, InstructionCode mc) {
	u32 a = self->regs.gpr[mc.rs];
	u32 b = self->regs.gpr[mc.rt];
	self->regs.gpr[mc.rd] = ((~a)&b)|(a&(~b));
}//38

void SLL(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = self->regs.gpr[mc.rt] << mc.sa;
}//0
void SRL(Cpu* self, InstructionCode mc) {
	u32 value = self->regs.gpr[mc.rt];
	self->regs.gpr[mc.rd] = ( value >> (mc.sa) ) | ( value << (32 - mc.sa) );
}//2

void SLT(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = (u32)(self->regs.gpr[mc.rs] < self->regs.gpr[mc.rt]);
}//42!!!

void LW(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rt] = MemMap_read_word(&self->mem, (i32)(self->regs.gpr[mc.rs]) + (i16)(mc.immediat));
}//35 I
void SW(Cpu* self, InstructionCode mc) {
	MemMap_write_word(&self->mem, (i32)(self->regs.gpr[mc.rs]) + (i16)(mc.immediat), self->regs.gpr[mc.rt]);
}//43 I
void LUI(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rt] = 0;
	self->regs.gpr[mc.rt] += (u32)(mc.immediat<<16);
}
void MFHI(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = self->regs.hi;
}//16
void MHLO(Cpu* self, InstructionCode mc) {
	self->regs.gpr[mc.rd] = self->regs.lo;
}//18

void BEQ(Cpu* self, InstructionCode mc) {
	if (self->regs.gpr[mc.rs] == self->regs.gpr[mc.rt]){
		self->regs.pc += (i16)((mc.immediat)<<2);
	}
}//4 I
void BNE(Cpu* self, InstructionCode mc) {
	if (self->regs.gpr[mc.rs] != self->regs.gpr[mc.rt]){
		self->regs.pc += (i16)((mc.immediat)<<2);
	}
}//5 I
void BGTZ(Cpu* self, InstructionCode mc) {
	if ((i32)self->regs.gpr[mc.rs] > 0){
		self->regs.pc += (i16)((mc.immediat)<<2);
	}
}//7 I
void BLEZ(Cpu* self, InstructionCode mc) {
	if ((i32)self->regs.gpr[mc.rs] <= 0){
		self->regs.pc += (i16)((mc.immediat)<<2);
	}
}//6 I
void J(Cpu* self, InstructionCode mc) {
	self->regs.pc += (i32)(mc.target<<2);
}//2 J
void JAL(Cpu* self, InstructionCode mc) {
	self->regs.gpr[RA] = self->regs.pc;
	self->regs.pc += (i32)(mc.target<<2);
}//3 J
void JR(Cpu* self, InstructionCode mc) {
	self->regs.pc = self->regs.gpr[mc.rs];
}//8


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
