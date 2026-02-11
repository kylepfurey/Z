// .h
// Z Foreign Function Interface Class
// by Kyle Furey

#ifndef ZLANG_FFI_H
#define ZLANG_FFI_H

#include <Types.h>

/** A handle to a dynamic library. */
typedef struct {
#ifdef ZLANG_WINDOWS
    /** The handle to the dynamic library. */
    HMODULE handle;
#else
    /** The handle to the dynamic library. */
    void *handle;
#endif
} ZLibrary;

/** Cached data related to an FFI call. */
typedef struct {
} ZFFI;

/** Initializes a new dynamic library. */
ZLANG_API ZBool ZLibrary_new(ZLibrary *self, ZString name);

/** Returns a function pointer from a library via its name. */
ZLANG_API ZFunc ZLibrary_get(ZLibrary *self, ZString func);

/** Cleans up all memory owned by a dynamic library. */
ZLANG_API void ZLibrary_delete(ZLibrary *self);

/** Initializes a new FFI call. */
ZLANG_API ZBool ZFFI_new(ZFFI *self);

/** Cleans up all memory owned by an FFI call. */
ZLANG_API void ZFFI_delete(ZFFI *self);

#endif // ZLANG_FFI_H
