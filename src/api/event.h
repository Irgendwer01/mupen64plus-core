#if !defined(API_EVENT_H)
#define API_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m64p_types.h"

typedef void(*EventCallback)();
typedef void(*EventIntCallback)(int);

extern EventCallback gVICallback;
extern EventIntCallback gResetCallback;
extern EventCallback gPauseCallback;

EXPORT void CALL VISetCallback(EventCallback callback);
EXPORT void CALL ResetSetCallback(EventIntCallback callback);
EXPORT void CALL PauseSetCallback(EventCallback callback);

#ifdef __cplusplus
}
#endif

#endif

