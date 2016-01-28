#ifndef TYPES_H
#define TYPES_H


//type de base pour un octet de mémoire
typedef unsigned char u8;
typedef signed char i8;

typedef unsigned short int u16;
typedef short int i16;
//type de base pour @ et registres
typedef unsigned long int u32;
typedef signed long int i32;

typedef unsigned long long i64;
//type utilitaire pour extraire les octets de u32 (passer par un cast)
typedef union {
  u32 word;
  struct {
  	u8 o4: 8;
  	u8 o3: 8;
	  u8 o2: 8;
	  u8 o1: 8;
  };
}u32Bytes;

typedef double u64;

typedef union {
	i64 raw;
	struct {
		u32 lo: 32;
		u32 hi: 32;
	};
}u64hilo;


#endif
