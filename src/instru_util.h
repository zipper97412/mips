#ifndef INSTRUUTIL_H
#define INSTRUUTIL_H


typedef union {
  u32 raw;
  struct {
    u32 fn: 6;
    u32 sa: 5;
    u32 rd: 5;
    u32 rt: 5;
    u32 rs: 5;
    u32 op: 6;
  };
  struct {
    u32 im: 16;
  };
  struct {
    u32 tg: 26;
  };
}InstructionCode;


#endif
