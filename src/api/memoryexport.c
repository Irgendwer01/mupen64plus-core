#include "api/memoryexport.h"
#include "device/device.h"

extern struct device g_dev;

#define VADDR_MASK (0x0FFFFFFF)

#ifdef WIN32
#define bswap32(x) ((uint32_t)_byteswap_ulong(x))
#define bswap64(x) ((uint64_t)_byteswap_uint64(x))
#else
#define bswap32(x) ((uint32_t)__builtin_bswap32(x))
#define bswap64(x) ((uint32_t)__builtin_bswap64(x))
#endif

extern void* g_mem_base;

EXPORT void* CALL Memory_GetBaseAddress(void) {
    return (u8*)mem_base_u32(g_mem_base, MM_RDRAM_DRAM);
}

EXPORT void* CALL ROM_GetBaseAddress(void) {
    return g_dev.cart.cart_rom.rom;
}

EXPORT u32 CALL ROM_GetBaseSize(void) {
    return g_dev.cart.cart_rom.rom_size;
}

EXPORT void CALL InvalidateCachedCode(void) {
#ifdef NEW_DYNAREC
    invalidate_cached_code_new_dynarec(&g_dev.r4300, 0, 0);
#else
    invalidate_r4300_cached_code(&g_dev.r4300, 0, 0);
#endif
}

