#include "cpu.h"
#include "mem.h"
#include "type.h"
#include "instru_util.h"
#include <stdio.h>
#include "runners.h"

int main() {
  u8 ramTab[1024];
  RAM ram = RAM_new(ramTab,1024);
  MemMap memmap = MemMap_new(&ram, 42, 42+1024);
  Cpu cpu = Cpu_new(memmap);
  Cpu_display(&cpu);
  printf("memtest word:\n");
  printf("ecriture:\n");
  MemMap_write_word(&memmap, 42+1020, 0x11223344);
  MemMap_display(&memmap);
  printf("lecture:\n");
  printf("%#010x\n",(unsigned int)MemMap_read_word(&memmap, 42+1020));
  InstructionCode ins;
  ins.raw = 0x4210841;
  int ok = 0;
  ok += (ins.raw == 0x4210841);
  ok += (ins.special == 1);
  ok += (ins.sa == 1);
  ok += (ins.rd == 1);
  ok += (ins.rt == 1);
  ok += (ins.rs == 1);
  ok += (ins.op == 1);
  ok += (ins.immediat == 0x841);
  ok += (ins.target == 0x210841);
  printf("test lecture champ d'instruction:\nun 9 doit apparaitre ici:%d\n", ok);
  ins.immediat = 1;
  ok = 0;
  ok += (ins.raw == 0x4210001);
  ins.target = 1;
  ok += (ins.raw == 0x4000001);
  printf("test ecriture champ insruction:\nun 2 doit apparaitre ici:%d\n", ok);

  interactif();



  return 0;
}
