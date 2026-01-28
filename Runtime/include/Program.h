// .h
// Z Program Class
// by Kyle Furey

#ifndef ZLANG_PROGRAM_H
#define ZLANG_PROGRAM_H

#include <Coroutine.h>
#include <FileStream.h>

/** All data related to the runtime of a single Z program. */
typedef struct {
    struct {
        /**
         * An array of pointers to coroutines (each coroutine slot).
         * A NULL pointer indicates an inactive slot.
         */
        ZCoroutine **array;

        /** The index of the current coroutine slot. */
        ZUShort index;

        /** The total number of active coroutine slots. */
        ZUShort count;

        /** The size of the coroutine slot array. */
        ZUShort capacity;

        /** The index of the next inactive coroutine slot. */
        ZUShort next;
    } coroutines;

    struct {
        /** An array of pointers to file streams. */
        ZFileStream **array;

        /** The total number of loaded files. */
        ZUShort count;

        /** The size of the file stream array. */
        ZUShort capacity;
    } fileStreams;
} ZProgram;

/** Initializes a new Z program using a stack-allocated coroutine and file stream. */
ZLANG_API ZBool ZProgram_new(ZProgram *self, ZCoroutine *coroutine, ZFileStream *fileStream);

/** Starts an additional coroutine and sets <handle> to its index. */
ZLANG_API ZBool ZProgram_startCoroutine(ZProgram *self, ZULong offset, ZUShort *handle);

/** Stops the coroutine with <handle>. */
ZLANG_API ZBool ZProgram_stopCoroutine(ZProgram *self, ZUShort handle);

/** Loads a .zlib file into a Z program. */
ZLANG_API ZBool ZProgram_loadFile(ZProgram *self, ZString path);

/** Executes the next step in a Z program. Returns whether the program can continue. */
ZLANG_API ZBool ZProgram_run(ZProgram *self);

/** Cleans up all memory owned by a Z program. */
ZLANG_API void ZProgram_delete(ZProgram *self);

#endif // ZLANG_PROGRAM_H
