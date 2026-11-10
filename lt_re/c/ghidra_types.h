/* Types used by Ghidra's decompiler output. Target: 32-bit x86 (use -m32). */
#ifndef GHIDRA_TYPES_H
#define GHIDRA_TYPES_H
#include <stdint.h>
#include <stddef.h>
typedef unsigned char undefined, undefined1, byte, uchar, bool8;
typedef uint16_t undefined2, ushort, word;
typedef uint32_t undefined4, uint, dword, ulong;
typedef uint64_t undefined8, ulonglong, qword;
typedef int64_t longlong;
typedef unsigned int code_ptr_dummy;
typedef int (*code)();
typedef char sbyte_dummy;
typedef struct { uint8_t b[3]; } undefined3;
typedef struct { uint8_t b[5]; } undefined5;
typedef struct { uint8_t b[6]; } undefined6;
typedef struct { uint8_t b[7]; } undefined7;
#define CONCAT11(a,b) ((uint16_t)(((uint16_t)(a)<<8)|(uint8_t)(b)))
#define CONCAT22(a,b) ((uint32_t)(((uint32_t)(uint16_t)(a)<<16)|(uint16_t)(b)))
#define CONCAT44(a,b) ((uint64_t)(((uint64_t)(uint32_t)(a)<<32)|(uint32_t)(b)))
static inline uint64_t _bd(double x){uint64_t r;__builtin_memcpy(&r,&x,8);return r;}
static inline uint64_t _bf(float x){uint32_t r;__builtin_memcpy(&r,&x,4);return r;}
static inline uint64_t _bi(uint64_t x){return x;}
#define _BITS(x) _Generic((x),double:_bd,float:_bf,default:_bi)(x)
#define SUB41(x,n) ((uint8_t)(_BITS(x)>>(8*(n))))
#define SUB42(x,n) ((uint16_t)(_BITS(x)>>(8*(n))))
#define SUB84(x,n) ((uint32_t)(_BITS(x)>>(8*(n))))
#define ZEXT14(x) ((uint32_t)(uint8_t)(x))
#define ZEXT24(x) ((uint32_t)(uint16_t)(x))
#define ZEXT48(x) ((uint64_t)(uint32_t)(x))
#define SEXT14(x) ((int32_t)(int8_t)(x))
#define SEXT24(x) ((int32_t)(int16_t)(x))
#define CARRY4(a,b) ((uint32_t)(a)+(uint32_t)(b)<(uint32_t)(a))
#define SBORROW4(a,b) ((((int32_t)(a)<0)!=((int32_t)(b)<0))&&(((int32_t)(a)<0)!=((int32_t)((a)-(b))<0)))
#define SCARRY4(a,b) ((((int32_t)(a)<0)==((int32_t)(b)<0))&&(((int32_t)(a)<0)!=((int32_t)((a)+(b))<0)))
#define halt_baddata() __builtin_trap()
#define __thiscall __attribute__((thiscall))
#define __fastcall __attribute__((fastcall))
#define __stdcall __attribute__((stdcall))
#define __cdecl __attribute__((cdecl))
#ifndef __cplusplus
#include <stdbool.h>
#endif
typedef long double float10;

#include "lt_types.h"
#include "lt_globals.h"
#include "lt_protos.h"
#endif
