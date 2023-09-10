#include "api/memoryexport.h"
#include "device/device.h"

#include <stdio.h>
#include <stdlib.h>

extern struct device g_dev;

extern u32* mem_base_u32(MemoryBase* mem_base, uint32_t address);

ML64_CodeCallbackNode* g_ml64_codecallback_head = NULL;
u32 current_uuid = 0;

EXPORT void* CALL Memory_GetBaseAddress(void) {
    return g_mem_base.rdram;
}

EXPORT void* CALL ROM_GetBaseAddress(void) {
    return g_mem_base.cartrom;
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

EXPORT void CALL InvalidateSpecificCachedCode(u32 address, u32 size) {
#ifdef NEW_DYNAREC
    invalidate_cached_code_new_dynarec(&g_dev.r4300, address, size);
#else
    invalidate_r4300_cached_code(&g_dev.r4300, address, size);
#endif
}

ML64_CodeCallbackNode* CreateNode(u32 address, Ml64_CodeCallbackFn pfn, u32 uuid) {
    ML64_CodeCallbackNode* newNode = (ML64_CodeCallbackNode*)malloc(sizeof(ML64_CodeCallbackNode));
    if (!newNode) {
        return NULL;
    }
    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->address = address;
    newNode->pfn = pfn;
    newNode->uuid = uuid;
    return newNode;
}

void AppendNode(ML64_CodeCallbackNode* newNode) {
    ML64_CodeCallbackNode* temp;

    if (!g_ml64_codecallback_head) {
        g_ml64_codecallback_head = newNode;
        return;
    }

    temp = g_ml64_codecallback_head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void RemoveNode(u32 uuid) {
    ML64_CodeCallbackNode* temp = g_ml64_codecallback_head;
    while (temp) {
        if (temp->uuid == uuid) {
            if (!temp->prev) {
                g_ml64_codecallback_head = temp->next;
                if (g_ml64_codecallback_head) {
                    g_ml64_codecallback_head->prev = NULL;
                }
            }
            else {
                temp->prev->next = temp->next;
                if (temp->next) {
                    temp->next->prev = temp->prev;
                }
            }
            free(temp);
            return;
        }
        temp = temp->next;
    }
}


EXPORT u32 CALL InstallCodeCallback(u32 address, Ml64_CodeCallbackFn pfn) {
    ML64_CodeCallbackNode* newNode = CreateNode(address, pfn, current_uuid);
    if (!newNode) {
        return -1;
    }
    AppendNode(newNode);
    InvalidateSpecificCachedCode(address, 8);
    return current_uuid++;
}

EXPORT void CALL UninstallCodeCallback(u32 uuid) {
    RemoveNode(uuid);
}

