#include "cpu.h"
#include "mem.h"
#include "type.h"
#include "instru_util.h"
#include <stdio.h>

int main() {
  RAM ram = RAM_new();
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
  ok += (ins.fn == 1);
  ok += (ins.sa == 1);
  ok += (ins.rd == 1);
  ok += (ins.rt == 1);
  ok += (ins.rs == 1);
  ok += (ins.op == 1);
  ok += (ins.im == 0x841);
  ok += (ins.tg == 0x210841);
  printf("test lecture champ d'instruction:\nun 9 doit apparaitre ici:%d\n", ok);
  ins.im = 1;
  ok = 0;
  ok += (ins.raw == 0x4210001);
  ins.tg = 1;
  ok += (ins.raw == 0x4000001);
  printf("test ecriture champ insruction:\nun 2 doit apparaitre ici:%d\n", ok);



  return 0;
}
