#ifndef MEM_H
#define MEM_H
#include "type.h"

#define RAM_OFFSET 42

typedef struct RAM {
  u8 data[1024];
} RAM;
RAM RAM_new();
void RAM_write(RAM* self, u32 rel_addr, u8 data);
u8 RAM_read(RAM* self, u32 rel_addr);
void RAM_display(RAM* self);

typedef struct MemMap {
  RAM* ram;
  u32 ram_offset;
  //IO* io;
} MemMap;
MemMap MemMap_new(RAM* ram);
void MemMap_write(MemMap* self, u32 addr, u8 data);
u8 MemMap_read(MemMap* self, u32 addr);
void MemMap_display(MemMap* self);



#endif
