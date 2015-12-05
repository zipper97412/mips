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
  /*
  InstructionCode i;
  i.raw = 0xffffffff;
  printf("%x %x %x %x %x %x %x\n",(unsigned int)i.raw, i.rtype.op, i.rtype.rs, i.rtype.rt, i.rtype.rd, i.rtype.sa, i.rtype.fn);
  printf("%x %x %x %x %x\n",(unsigned int)i.raw, i.itype.op, i.itype.rs, i.itype.rt, (unsigned int)i.itype.im);
  printf("%x %x %x\n",(unsigned int)i.raw, (unsigned int)i.jtype.op, (unsigned int)i.jtype.tg);
  i.raw = 0;
  i.jtype.op = 1;
  printf("%x\n",(unsigned int)i.raw);
  i.raw = 0;
  i.jtype.tg = 1;
  printf("%lx\n",(unsigned long)i.raw);
  printf("%lx\n",(unsigned long)&notOp);
  printf("%lx\n",(unsigned long)opcodeToFunc[41]);
  printf("%lx\n",(unsigned long)opcodeToFunc[42]);
  printf("%lx\n",(unsigned long)opcodeToFunc[43]);
  */
  printf("memtest word:\n");
  printf("ecriture:\n");
  MemMap_write_word(&memmap, 42+1020, 0x11223344);
  MemMap_display(&memmap);
  printf("lecture:\n");
  printf("%#010x\n",(unsigned int)MemMap_read_word(&memmap, 42+1020));
  InstructionCodeV2 ins;
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
