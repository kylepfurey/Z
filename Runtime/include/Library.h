// .h
// Z Dynamic Library Class
// by Kyle Furey

#ifndef ZLANG_LIBRARY_H
#define ZLANG_LIBRARY_H

#include <Types.h>

/** A handle to a dynamic library. */
typedef struct {
#ifdef ZLANG_WINDOWS

    /** The handle to the .dll dynamic library. */
    HMODULE handle;

#else

    /** The handle to the .so / .dylib dynamic library. */
    void *handle;

#endif
} ZLibrary;

/** Initializes a new dynamic library. */
ZLANG_API ZBool ZLibrary_new(ZLibrary *self, ZString name);

/** Returns a function pointer from a dynamic library via its name. */
ZLANG_API ZFunc ZLibrary_get(ZLibrary *self, ZString func);

/** Cleans up all memory owned by a dynamic library. */
ZLANG_API void ZLibrary_delete(ZLibrary *self);

#endif // ZLANG_LIBRARY_H
