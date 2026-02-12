// .h
// Z Dynamic Library Class
// by Kyle Furey

#ifndef ZLANG_LIBRARY_H
#define ZLANG_LIBRARY_H

#include <Vector.h>

/** A handle to a dynamic library. */
typedef struct {
#ifdef ZLANG_WINDOWS

    /** The handle to the .dll dynamic library. */
    HMODULE handle;

#else

    /** The handle to the .so / .dylib dynamic library. */
    void *handle;

#endif

    /** A vector of pointers to foreign function interfaces. */
    ZVector ffi;
} ZLibrary;

/** Metadata for a foreign function interface call. */
typedef struct {
} ZFFI;

/** Initializes a new dynamic library. */
ZLANG_API ZBool ZLibrary_new(ZLibrary *self, ZString name);

/** Returns a function pointer from a dynamic library via its name. */
ZLANG_API ZFunc ZLibrary_find(ZLibrary *self, ZString func);

/** Cleans up all memory owned by a dynamic library. */
ZLANG_API void ZLibrary_delete(ZLibrary *self);

/** Initializes a new foreign function interface. */
ZLANG_API ZBool ZFFI_new(ZFFI *self, ZCoroutine *coroutine);

/** Cleans up all memory owned by a foreign function interface. */
ZLANG_API void ZFFI_delete(ZFFI *self);

#endif // ZLANG_LIBRARY_H
