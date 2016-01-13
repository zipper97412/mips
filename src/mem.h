#ifndef MEM_H
#define MEM_H
#include "type.h"


typedef struct RAM {
  u8* data;
  int len;
} RAM;
RAM RAM_new(u8* ramTab, int len);
void RAM_write(RAM* self, u32 rel_addr, u8 data);
void RAM_write_word(RAM* self, u32 rel_addr, u32 data);

u8 RAM_read(RAM* self, u32 rel_addr);
u32 RAM_read_word(RAM* self, u32 rel_addr);

void RAM_display(RAM* self, u32 ram_begin);



typedef struct MemMap {
  RAM* ram;
  u32 ram_begin;
  u32 ram_end;
  RAM* prog;
  u32 prog_begin;
  u32 prog_end;
  //IO* io;
} MemMap;
MemMap MemMap_new(RAM* ram, u32 ram_begin, u32 ram_end, RAM* prog, u32 prog_begin, u32 prog_end);
void MemMap_write(MemMap* self, u32 addr, u8 data);
void MemMap_write_word(MemMap* self, u32 addr, u32 data);

u8 MemMap_read(MemMap* self, u32 addr);
u32 MemMap_read_word(MemMap* self, u32 addr);
void MemMap_display(MemMap* self);



#endif
