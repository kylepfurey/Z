// .h
// Z Coroutine Structure and Functions
// by Kyle Furey

#ifndef ZLANG_COROUTINE_H
#define ZLANG_COROUTINE_H

#include <FileStream.h>
#include <Stack.h>

#ifdef __cplusplus
extern "C" {
#endif

/** A single coroutine and the file it is executing. */
typedef struct {
    /** This coroutine's file stream. */
    ZFileStream file_stream;

    /** This coroutine's stack. */
    ZStack stack;
} ZCoroutine;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_COROUTINE_H
