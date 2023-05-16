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

static inline void* GetKSEG0Addr(u32 vaddr) {
    return (u8*)mem_base_u32(g_mem_base, MM_RDRAM_DRAM) + (vaddr & VADDR_MASK);
}

static inline u32 AlignAddress(u32 address) {
    return (address & VADDR_MASK) / 4;
}

EXPORT u64 CALL Memory_Read64(u32 address) {
    u64 hi = Memory_Read32(address + 4);
    u64 lo = Memory_Read32(address);
    return ((u64)(hi << 32) | (u64)lo);
}

EXPORT u32 CALL Memory_Read32(u32 address) {
    return *((u32*)GetKSEG0Addr(AlignAddress(address)));
}

EXPORT u16 CALL Memory_Read16(u32 address) {
    return (((u16)Memory_Read8(address) << 8) | ((u16)Memory_Read8(address + 1)));
}

EXPORT u8 CALL Memory_Read8(u32 address) {
    u32 offset = AlignAddress(address) * 4 + (3 - (address & 3));
    return *((u8*)GetKSEG0Addr(offset));
}

EXPORT f64 CALL Memory_ReadF64(u32 address) {
    return *((f64*)GetKSEG0Addr(address));
}

EXPORT f32 CALL Memory_ReadF32(u32 address) {
    return *((f32*)GetKSEG0Addr(address));
}

EXPORT void CALL Memory_Write64(u32 address, u64 value) {
    u64 hi = value >> 32;
    u64 lo = value & 0x00000000FFFFFFFF;
    Memory_Write32(address, hi);
    Memory_Write32(address + 4, lo);
}

EXPORT void CALL Memory_Write32(u32 address, u32 value) {
    *((u32*)GetKSEG0Addr(address)) = value;
}

EXPORT void CALL Memory_Write16(u32 address, u16 value) {
    Memory_Write8(address, value >> 8);
    Memory_Write8(address + 1, value & 0xFF);
}

EXPORT void CALL Memory_Write8(u32 address, u8 value) {
    u32 offset = AlignAddress(address) * 4 + (3 - (address & 3));
    *((u8*)GetKSEG0Addr(offset)) = value;
}

EXPORT void CALL Memory_WriteF64(u32 address, f64 value) {
    u64* val = &value;
    u64 hi = *val >> 32;
    u64 lo = *val & 0x00000000FFFFFFFF;
    Memory_Write32(address, hi);
    Memory_Write32(address + 4, lo);
}

EXPORT void CALL Memory_WriteF32(u32 address, f32 value) {
    *((f32*)GetKSEG0Addr(address)) = value;
}


EXPORT void* CALL Memory_GetBaseAddress(void) {
    return g_dev.rdram.dram;
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

