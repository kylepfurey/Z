// .h
// Z Foreign Function Interface Class
// by Kyle Furey

#ifndef ZLANG_FFI_H
#define ZLANG_FFI_H

#include <Types.h>

/** Cached data related to an FFI call. */
typedef struct {
    /** The FFI function to call. */
    void *func;
} ZFFI;

/** Initializes a new FFI call. */
ZLANG_API ZBool ZFFI_new(ZFFI *self);

/** Cleans up all memory owned by an FFI call. */
ZLANG_API void ZFFI_delete(ZFFI *self);

#endif // ZLANG_FFI_H
