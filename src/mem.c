#include "mem.h"
#include "type.h"
#include <stdlib.h>
#include <stdio.h>

MemMap MemMap_new(RAM* ram, u32 ram_begin, u32 ram_end, RAM* prog, u32 prog_begin, u32 prog_end) {

  if(ram_begin > ram_end || prog_begin > prog_end ||
    ( (ram_begin < prog_begin) && (prog_begin < ram_end) ) ||
    ( (ram_begin < prog_end) && (prog_end < ram_end) ) ) {
      printf("erreur de mappage de mémoire\n");
      exit(1);
    }


  MemMap memmap = {
    ram: ram,
    ram_begin: ram_begin,
    ram_end: ram_end,
    prog: prog,
    prog_begin: prog_begin,
    prog_end: prog_end
  };
  return memmap;
}
void MemMap_write(MemMap* self, u32 addr, u8 data) {
  if ( (addr >= self->ram_begin) && (addr < self->ram_end) ) {
    RAM_write(self->ram, addr - self->ram_begin, data);
  }
  else if ( (addr >= self->prog_begin) && (addr < self->prog_end) ) {
    RAM_write(self->prog, addr - self->prog_begin, data);
    return;
  }
  else {
    printf("erreur acces @%#010x non valide\n", (unsigned int)addr);
    exit(1);
  }
}
void MemMap_write_word(MemMap* self, u32 addr, u32 data){
  if ( (addr >= self->ram_begin) && (addr < self->ram_end - 3) ) {
    RAM_write_word(self->ram, addr - self->ram_begin, data);
  }
  else if ( (addr >= self->prog_begin) && (addr < self->prog_end - 3) ) {
    RAM_write_word(self->prog, addr - self->prog_begin, data);
  }
  else {
    printf("erreur acces @%#010x non valide\n", (unsigned int)addr);
    exit(1);
  }
}

u8 MemMap_read(MemMap* self, u32 addr) {
  if ( (addr >= self->ram_begin) && (addr < self->ram_end) ) {
    return RAM_read(self->ram, addr - self->ram_begin);
  }
  else if ( (addr >= self->prog_begin) && (addr < self->prog_end) ) {
    return RAM_read(self->prog, addr - self->prog_begin);
  }
  else {
    printf("erreur acces @%#010x non valide\n", (unsigned int)addr);
    exit(1);
  }
}
u32 MemMap_read_word(MemMap* self, u32 addr) {
  if ( (addr >= self->ram_begin) && (addr < self->ram_end - 3) ) {
    return RAM_read_word(self->ram, addr - self->ram_begin);
  }
  else if ( (addr >= self->prog_begin) && (addr < self->prog_end - 3) ) {
    return RAM_read_word(self->prog, addr - self->prog_begin);
  }
  else {
    printf("erreur acces @%#010x non valide\n", (unsigned int)addr);
    exit(1);
  }
}
void MemMap_display(MemMap* self) {
	printf("Mémoire de donnée\n");
  RAM_display(self->ram, self->ram_begin);
  printf("memoire de programme (rien si interractif)\n");
  RAM_display(self->prog, self->prog_begin);
}


RAM RAM_new(u8* tab, int len) {
  RAM ram;
  ram.data = tab;
  ram.len = len;
  return ram;
}
void RAM_write(RAM* self, u32 rel_addr, u8 data) {
  self->data[rel_addr] = data;
}
void RAM_write_word(RAM* self, u32 rel_addr, u32 data){

  u8* temp = self->data;
  u32Bytes tempData = (u32Bytes)data;
  temp[rel_addr] = tempData.o1;
  temp[rel_addr+1] = tempData.o2;
  temp[rel_addr+2] = tempData.o3;
  temp[rel_addr+3] = tempData.o4;
}

u8 RAM_read(RAM* self, u32 rel_addr) {
  return self->data[rel_addr];
}
u32 RAM_read_word(RAM* self, u32 rel_addr) {
  u8* temp = self->data;
  u32Bytes ret;
  ret.o1 = temp[rel_addr];
  ret.o2 = temp[rel_addr+1];
  ret.o3 = temp[rel_addr+2];
  ret.o4 = temp[rel_addr+3];
  return ret.word;
}


void RAM_display(RAM* self, u32 ram_begin) {
  int i;
  if(self->len == 0) {
    return;
  }
  //printf("\nRAM(%#010x):\n",(unsigned int)ram_begin);
  for(i=0;i<self->len;i++) {
    if ((i%16) == 0) {
      printf("%#010x(%d):    \t[",(unsigned int)(i+ram_begin),i);
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
