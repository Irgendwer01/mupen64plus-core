#ifndef __MEMORY_BASE_H__
#define __MEMORY_BASE_H__

#define RDRAM_MEMORY_4MB_SIZE   (0x00400000)
#define RDRAM_MEMORY_8MB_SIZE   (0x00800000)
#define RDRAM_MEMORY_16MB_SIZE  (0x01000000)
#define RDRAM_MEMORY_SIZE       (0x40000000)
#define RDRAM_REGISTER_COUNT (10)
#define RDRAM_REGISTER_COUNT (10)

#define CART_ROM_MAX_SIZE (0x4000000)
#define DD_ROM_MAX_SIZE (0x400000)

#define SP_MEM_SIZE (0x2000)
#define PIF_ROM_SIZE (0x7C0)
#define PIF_RAM_SIZE (0x40)
#define PIF_CHANNELS_COUNT (5)

#define MB_RDRAM_DRAM_ALIGNMENT_REQUIREMENT (64 * 1024)
#define MB_ALIGNMENT_REQUIREMENT (0x40)
#define MM_END (0x20000000)

typedef struct {
    void* rdram;
    void* rdram_extra;
    void* cartrom;
    void* rspmem;
    void* ddrom;
    void* pifmem;
} MemoryBase;

#endif

