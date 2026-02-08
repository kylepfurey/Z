// .h
// Z Program Class
// by Kyle Furey

#ifndef ZLANG_PROGRAM_H
#define ZLANG_PROGRAM_H

#include <Vector.h>
#include <Coroutine.h>
#include <FileStream.h>

/** All data related to the runtime of a single Z program. */
typedef struct {
    /**
     * A vector of pointers to coroutines (each coroutine slot).
     * A NULL pointer indicates an inactive slot.
     */
    ZVector coroutines;

    /** The index of the current coroutine slot. */
    ZUInt current;

    /** The index of the next inactive coroutine slot. */
    ZUInt next;

    /** A vector of pointers to file streams in global order. */
    ZVector fileStreams;
} ZProgram;

/** Initializes a new Z program using a stack-allocated coroutine and file stream. */
ZLANG_API ZBool ZProgram_new(ZProgram *self, ZCoroutine *coroutine, ZFileStream *fileStream);

/** Executes the next step in a Z program. Returns whether the program can continue. */
ZLANG_API ZBool ZProgram_run(ZProgram *self);

/** Cleans up all memory owned by a Z program. */
ZLANG_API void ZProgram_delete(ZProgram *self);

#endif // ZLANG_PROGRAM_H
