// .h
// Z Program Class
// by Kyle Furey

#ifndef ZLANG_PROGRAM_H
#define ZLANG_PROGRAM_H

#include <Coroutine.h>
#include <FileStream.h>

#ifdef __cplusplus
extern "C" {
#endif

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

        /** The size of the file stream array. */
        ZUShort capacity;
    } fileStreams;
} ZProgram;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_PROGRAM_H
