#if !defined(API_MEMORYEXPORT_H)
#define API_MEMORYEXPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m64p_types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

EXPORT u64 CALL Memory_Read64(u32 address);
EXPORT u32 CALL Memory_Read32(u32 address);
EXPORT u16 CALL Memory_Read16(u32 address);
EXPORT u8 CALL Memory_Read8(u32 address);
EXPORT f64 CALL Memory_ReadF64(u32 address);
EXPORT f32 CALL Memory_ReadF32(u32 address);

EXPORT void CALL Memory_Write64(u32 address, u64 value);
EXPORT void CALL Memory_Write32(u32 address, u32 value);
EXPORT void CALL Memory_Write16(u32 address, u16 value);
EXPORT void CALL Memory_Write8(u32 address, u8 value);
EXPORT void CALL Memory_WriteF64(u32 address, f64 value);
EXPORT void CALL Memory_WriteF32(u32 address, f32 value);

EXPORT void* CALL Memory_GetBaseAddress(void);
EXPORT void* CALL ROM_GetBaseAddress(void);

EXPORT u32 CALL ROM_GetBaseSize(void);

EXPORT void CALL InvalidateCachedCode(void);

#ifdef __cplusplus
}
#endif

#endif

