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

EXPORT void* CALL Memory_GetBaseAddress(void);
EXPORT void* CALL ROM_GetBaseAddress(void);

EXPORT u32 CALL ROM_GetBaseSize(void);

EXPORT void CALL InvalidateCachedCode(void);

#ifdef __cplusplus
}
#endif

#endif

