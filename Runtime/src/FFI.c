// .c
// Z Foreign Function Interface Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new dynamic library. */
ZBool ZLibrary_new(ZLibrary *self, ZString name) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(name != NULL, "<name> was NULL!");
    ZULong nameLen = strlen(name);
    // TODO .dll, .dylib, .so
}

/** Returns a function pointer from a library via its name. */
ZFunc ZLibrary_get(ZLibrary *self, ZString func) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(func != NULL, "<func> was NULL!");
#ifdef ZLANG_WINDOWS
    return (ZFunc) GetProcAddress(self->handle, func);
#else
    return (ZFunc) dlsym(self->handle, func);
#endif
}

/** Cleans up all memory owned by a dynamic library. */
void ZLibrary_delete(ZLibrary *self) {
    Zassert(self != NULL, "<self> was NULL!");
#ifdef ZLANG_WINDOWS
    FreeLibrary(self->handle);
#else
    dlclose(self->handle);
#endif
    self->handle = NULL;
}

/** Initializes a new FFI call. */
ZBool ZFFI_new(ZFFI *self) {
    Zassert(self != NULL, "<self> was NULL!");
}

/** Cleans up all memory owned by an FFI call. */
void ZFFI_delete(ZFFI *self) {
    Zassert(self != NULL, "<self> was NULL!");
}
