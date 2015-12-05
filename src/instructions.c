#include "cpu.h"

void notOp(Cpu* self, InstructionCode mc) {}
void test(Cpu* self, InstructionCode mc) {}

OperationFunc opcodeToFunc[64] = {
  [0 ... 41] = &notOp,
  &test,
  [43 ... 63] = &notOp
};
