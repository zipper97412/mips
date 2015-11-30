#include "cpu.h"
#include "mem.h"
#include "type.h"

int main() {
  RAM ram = RAM_new();
  MemMap memmap = MemMap_new(&ram);
  Cpu cpu = Cpu_new(memmap);
  Cpu_display(&cpu);



  return 0;
}
