// .h
// Z Coroutine Class
// by Kyle Furey

#ifndef ZLANG_COROUTINE_H
#define ZLANG_COROUTINE_H

#include <Stack.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The number of milliseconds a coroutine is alloted before context-switching. */
#define ZLANG_COROUTINE_DELAY_MS 100

/** A single coroutine containing a stack and file address. */
typedef struct {
    /** This coroutine's stack space. */
    ZStack stack;

    /** This coroutine's current global offset. */
    ZULong globalOffset;

    /** The delay in milliseconds before resuming this coroutine. */
    ZUInt delayMs;
} ZCoroutine;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_COROUTINE_H
