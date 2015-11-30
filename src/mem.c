#include "mem.h"
#include <stdlib.h>
#include <stdio.h>

MemMap MemMap_new(RAM* ram) {

  MemMap memmap;
  memmap.ram = ram;
  memmap.ram_offset = RAM_OFFSET;
  return memmap;
}
void MemMap_write(MemMap* self, u32 addr, u8 data) {
  if ( (addr >= self->ram_offset) && (addr < sizeof(self->ram->data)) ) {
    RAM_write(self->ram, addr-RAM_OFFSET, data);
    return;
  }
  else {
    printf("erreur acces @%x non valide\n", (int)addr);
    exit(1);
  }
}
u8 MemMap_read(MemMap* self, u32 addr) {
  if ( (addr >= self->ram_offset) && (addr < sizeof(self->ram->data)) ) {
    return RAM_read(self->ram, addr-RAM_OFFSET);
  }
  else {
    printf("erreur acces @%x non valide\n", (int)addr);
    exit(1);
  }
}
void MemMap_display(MemMap* self) {
  RAM_display(self->ram);
}


RAM RAM_new() {
  RAM ram;
  return ram;
}
void RAM_write(RAM* self, u32 rel_addr, u8 data) {
  self->data[rel_addr] = data;
}
u8 RAM_read(RAM* self, u32 rel_addr) {
  return self->data[rel_addr];
}
void RAM_display(RAM* self) {
  int i;
  printf("\nRAM(%#010x):\n",RAM_OFFSET);
  for(i=0;i<sizeof(self->data);i++) {
    if ((i%16) == 0) {
      printf("%#010x(%d):    \t[",(i+RAM_OFFSET),i);
    }
    printf("%02x",self->data[i]);
    if ( ((i%16) == 3) || ((i%16) == 7) || ((i%16) == 11) ){
      printf("] [");
    }
    if ((i%16) == 15) {
      printf("]\n");
    }
  }
}
