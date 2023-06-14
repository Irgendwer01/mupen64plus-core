#if !defined(MODLOADER_COMMON_H)
#define MODLOADER_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device/memory/memory.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define VADDR_MASK (0x0FFFFFFF)
#define VADDR_MAX (0x80000000 + RDRAM_MAX_SIZE)
#define MAX_PAGE (RDRAM_MAX_SIZE / 0x1000)

#ifdef __cplusplus
}
#endif

#endif