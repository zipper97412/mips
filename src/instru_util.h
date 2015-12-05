#ifndef INSTRUUTIL_H
#define INSTRUUTIL_H

//cet union permet de décomposer une instruction en plusieurs champs de bits
//en choisisant le type d'adressage. raw est l'instruction non décomposé
typedef union {
  u32 raw;
  struct {
    u32
      op: 6,
      sa: 5,
      rd: 5,
      rt: 5,
      rs: 5,
      fn: 6;
  } rtype;
  struct {
    u32
      im: 16,
      rt: 5,
      rs: 5,
      op: 6;
  } itype;
  struct {
    u32
      tg: 26,
      op: 6;
  } jtype;
}InstructionCode;

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
}InstructionCodeV2;


#endif
