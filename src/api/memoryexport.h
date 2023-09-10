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
EXPORT void CALL InvalidateSpecificCachedCode(u32 address, u32 size);

typedef void(*Ml64_CodeCallbackFn)(void);

EXPORT u32 CALL InstallCodeCallback(u32 address, Ml64_CodeCallbackFn pfn);
EXPORT void CALL UninstallCodeCallback(u32 uuid);

typedef struct ML64_CodeCallbackNode  {
	struct ML64_CodeCallbackNode* prev;
	struct ML64_CodeCallbackNode* next;
	Ml64_CodeCallbackFn pfn;
	u32 address;
	u32 uuid;
} ML64_CodeCallbackNode;

extern ML64_CodeCallbackNode* g_ml64_codecallback_head;

#ifdef __cplusplus
}
#endif

#endif

