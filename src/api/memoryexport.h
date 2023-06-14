#if !defined(API_MEMORYEXPORT_H)
#define API_MEMORYEXPORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m64p_types.h"
#include "modloader_common.h"

EXPORT void* CALL Memory_GetBaseAddress(void);
EXPORT void* CALL ROM_GetBaseAddress(void);

EXPORT u32 CALL ROM_GetBaseSize(void);

EXPORT void CALL InvalidateCachedCode(void);

#ifdef __cplusplus
}
#endif

#endif

