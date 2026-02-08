// .h
// Z Coroutine Class
// by Kyle Furey

#ifndef ZLANG_COROUTINE_H
#define ZLANG_COROUTINE_H

#include <Stack.h>
#include <Vector.h>

/** The number of milliseconds a coroutine is alloted before context-switching. */
#define ZLANG_COROUTINE_DELAY_MS 100

/** An index representing an empty coroutine handle. */
#define ZLANG_COROUTINE_NULL ((ZUInt) -1)

/** Stack memory and metadata for a single coroutine. */
typedef struct {
    /** This coroutine's stack space. */
    ZStack stack;

    /** The cached global offset of this coroutine in virtual memory. */
    ZULong globalOffset;

    /** This coroutine's index. */
    ZUInt index;

    /** The index of a remote coroutine this coroutine is waiting on. */
    ZUInt await;

    /** The delay in milliseconds before resuming this coroutine. */
    ZULong delayMs;

    /** A vector of handle pointers used to share this coroutine's return value. */
    ZVector dispatcher;
} ZCoroutine;

/** A pointer to a coroutine handle in a remote coroutine's stack. */
typedef struct {
    /** The index of the remote coroutine containing the coroutine handle. */
    ZUInt index;

    /** The offset from the bottom of the stack containing the coroutine handle. */
    ZUInt offset;
} ZHandlePointer;

#pragma pack(push, 1)

/** A handle used to receive the return value of a remote coroutine. */
typedef struct {
    /** Whether this handle contains the remote coroutine's return value. */
    ZBool valid;

    /**
     * If <valid> is false, this is the index of the remote coroutine.
     * If <valid> is true, this is the first 4 bytes of the remote coroutine's return value.
     */
    ZUInt index;
} __attribute__((packed)) ZHandle;

#pragma pack(pop)

/** Initializes a new Z coroutine. */
ZLANG_API ZBool ZCoroutine_new(ZCoroutine *self);

/** Cleans up all memory owned by a Z coroutine. */
ZLANG_API void ZCoroutine_delete(ZCoroutine *self);

#endif // ZLANG_COROUTINE_H
