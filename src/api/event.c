#include "api/event.h"

EventCallback gVICallback = NULL;
EventIntCallback gResetCallback = NULL;
EventCallback gPauseCallback = NULL;

EXPORT void CALL VISetCallback(EventCallback callback) {
    gVICallback = callback;
}

EXPORT void CALL ResetSetCallback(EventIntCallback callback) {
    gResetCallback = callback;
}

EXPORT void CALL PauseSetCallback(EventCallback callback) {
    gPauseCallback = callback;
}



