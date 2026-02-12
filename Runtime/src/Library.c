// .c
// Z Dynamic Library Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new dynamic library. */
ZBool ZLibrary_new(ZLibrary *self, ZString name) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(name != NULL, "<name> was NULL!");
    if (!ZVector_new(&self->types, ZLANG_DEFAULT_CAPACITY)) {
        Zerror("Could not initialize dynamic library types vector!");
        return false;
    }
    if (!ZVector_new(&self->ffi, ZLANG_DEFAULT_CAPACITY)) {
        Zerror("Could not initialize dynamic library FFI vector!");
        return false;
    }
    ZULong nameLen = strlen(name);
    ZChar *buffer;

#ifdef ZLANG_WINDOWS

    // *.dll

    buffer = (ZChar *) malloc(nameLen + 5); // [.][d][l][l][\0]
    if (buffer == NULL) {
        Zerror("Could not allocate buffer for dynamic library name!");
        return false;
    }
    memcpy(buffer, name, nameLen);
    buffer[nameLen] = '.';
    buffer[nameLen + 1] = 'd';
    buffer[nameLen + 2] = 'l';
    buffer[nameLen + 3] = 'l';
    buffer[nameLen + 4] = '\0';
    self->handle = LoadLibraryA(buffer);
    if (self->handle == NULL) {
        free(buffer);
        ZString home = getenv(ZLANG_HOME_VAR);
        if (home == NULL) {
            Zerror("Dynamic library not found in directory!");
            return false;
        }
        ZULong homeLen = strlen(home);
        buffer = (ZChar *) malloc(homeLen + nameLen + 6); // [/]...[.][d][l][l][\0]
        if (buffer == NULL) {
            Zerror("Could not allocate buffer for Z_HOME path + dynamic library name!");
            return false;
        }
        memcpy(buffer, home, homeLen);
        buffer[homeLen] = ZLANG_PATH_SEPARATOR;
        memcpy(buffer + homeLen + 1, name, nameLen);
        ZULong len = homeLen + nameLen;
        buffer[++len] = '.';
        buffer[++len] = 'd';
        buffer[++len] = 'l';
        buffer[++len] = 'l';
        buffer[++len] = '\0';
        self->handle = LoadLibraryA(buffer);
        free(buffer);
        if (self->handle == NULL) {
            Zerror("Dynamic library not found in directory or Z_HOME!");
            return false;
        }
    } else {
        free(buffer);
    }
    return true;

#else

#ifdef ZLANG_POSIX

#ifdef ZLANG_MACOS

    // lib*.dylib

    buffer = (ZChar *) malloc(nameLen + 10); // [l][i][b]...[.][d][y][l][i][b][\0]
    if (buffer == NULL) {
        Zerror("Could not allocate buffer for dynamic library name!");
        return false;
    }
    buffer[0] = 'l';
    buffer[1] = 'i';
    buffer[2] = 'b';
    memcpy(buffer + 3, name, nameLen);
    buffer[nameLen + 3] = '.';
    buffer[nameLen + 4] = 'd';
    buffer[nameLen + 5] = 'y';
    buffer[nameLen + 6] = 'l';
    buffer[nameLen + 7] = 'i';
    buffer[nameLen + 8] = 'b';
    buffer[nameLen + 9] = '\0';
    self->handle = dlopen(buffer, RTLD_NOW | RTLD_GLOBAL);
    if (self->handle == NULL) {
        free(buffer);
        ZString home = getenv(ZLANG_HOME_VAR);
        if (home == NULL) {
            Zerror("Dynamic library not found in directory!");
            return false;
        }
        ZULong homeLen = strlen(home);
        buffer = (ZChar *) malloc(homeLen + nameLen + 11); // [/][l][i][b]...[.][d][y][l][i][b][\0]
        if (buffer == NULL) {
            Zerror("Could not allocate buffer for Z_HOME path + dynamic library name!");
            return false;
        }
        memcpy(buffer, home, homeLen);
        buffer[homeLen] = ZLANG_PATH_SEPARATOR;
        buffer[homeLen + 1] = 'l';
        buffer[homeLen + 2] = 'i';
        buffer[homeLen + 3] = 'b';
        memcpy(buffer + homeLen + 4, name, nameLen);
        ZULong len = homeLen + nameLen + 3;
        buffer[++len] = '.';
        buffer[++len] = 'd';
        buffer[++len] = 'y';
        buffer[++len] = 'l';
        buffer[++len] = 'i';
        buffer[++len] = 'b';
        buffer[++len] = '\0';
        self->handle = dlopen(buffer, RTLD_NOW | RTLD_GLOBAL);
        free(buffer);
        if (self->handle == NULL) {
            Zerror("Dynamic library not found in directory or Z_HOME!");
            return false;
        }
    } else {
        free(buffer);
    }
    return true;

#else

    // lib*.so

    buffer = (ZChar *) malloc(nameLen + 7); // [l][i][b]...[.][s][o][\0]
    if (buffer == NULL) {
        Zerror("Could not allocate buffer for dynamic library name!");
        return false;
    }
    buffer[0] = 'l';
    buffer[1] = 'i';
    buffer[2] = 'b';
    memcpy(buffer + 3, name, nameLen);
    buffer[nameLen + 3] = '.';
    buffer[nameLen + 4] = 's';
    buffer[nameLen + 5] = 'o';
    buffer[nameLen + 6] = '\0';
    self->handle = dlopen(buffer, RTLD_NOW | RTLD_GLOBAL);
    if (self->handle == NULL) {
        free(buffer);
        ZString home = getenv(ZLANG_HOME_VAR);
        if (home == NULL) {
            Zerror("Dynamic library not found in directory!");
            return false;
        }
        ZULong homeLen = strlen(home);
        buffer = (ZChar *) malloc(homeLen + nameLen + 8); // [/][l][i][b]...[.][s][o][\0]
        if (buffer == NULL) {
            Zerror("Could not allocate buffer for Z_HOME path + dynamic library name!");
            return false;
        }
        memcpy(buffer, home, homeLen);
        buffer[homeLen] = ZLANG_PATH_SEPARATOR;
        buffer[homeLen + 1] = 'l';
        buffer[homeLen + 2] = 'i';
        buffer[homeLen + 3] = 'b';
        memcpy(buffer + homeLen + 4, name, nameLen);
        ZULong len = homeLen + nameLen + 3;
        buffer[++len] = '.';
        buffer[++len] = 's';
        buffer[++len] = 'o';
        buffer[++len] = '\0';
        self->handle = dlopen(buffer, RTLD_NOW | RTLD_GLOBAL);
        free(buffer);
        if (self->handle == NULL) {
            Zerror("Dynamic library not found in directory or Z_HOME!");
            return false;
        }
    } else {
        free(buffer);
    }
    return true;

#endif

#endif

#endif

    Zerror("Cannot load with unknown dynamic library format!");
    return false;
}

/** Returns a function pointer from a dynamic library via its name. */
ZFunc ZLibrary_find(ZLibrary *self, ZString func) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(func != NULL, "<func> was NULL!");
    Zassert(self->handle != NULL, "<self>'s handle was NULL!");

#ifdef ZLANG_WINDOWS

    return (ZFunc) GetProcAddress(self->handle, func);

#else

#ifdef ZLANG_POSIX

    return (ZFunc) dlsym(self->handle, func);

#endif

#endif

    Zerror("Cannot get function with unknown dynamic library format!");
    return NULL;
}

/**
 * Calls a foreign function with the given index.
 * If this is the first call, this prepares the function instead.
 */
ZBool ZLibrary_call(ZLibrary *self, ZFileStream *file, ZUInt index) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(file != NULL, "<file> was NULL!");
    if (index < self->ffi.count) {
        ZCall *call = (ZCall *) ZVector_get(&self->ffi, index);
        void *ret;
        void **args;
        // TODO: Walk argument and return types for call
        ffi_call(&call->cif, call->func, ret, args);
        return true;
    }
    if (index > self->ffi.count) {
        Zerror("Cannot load dynamic libraries out of order!");
        return false;
    }
    ZCall *call = (ZCall *) malloc(sizeof(ZCall));
    if (call == NULL) {
        Zerror("Could not allocate call for dynamic library!");
        return false;
    }
    ZByte len;
    if (!ZFileStream_nextByte(file, &len)) {
        Zerror("Could not get dynamic library function name length!");
        free(call);
        return false;
    }
    ZChar *name = (ZChar *) malloc(len + 1);
    if (name == NULL) {
        Zerror("Could not allocate buffer for dynamic library function name!");
        free(call);
        return false;
    }
    name[len] = '\0';
    if (!ZFileStream_nextArray(file, len, (ZByte *) &name)) {
        Zerror("Could not read dynamic library function name!");
        free(name);
        free(call);
        return false;
    }
    call->func = ZLibrary_find(self, name);
    free(name);
    if (call->func == NULL) {
        Zerror("Could not find dynamic library function with name!");
        free(call);
        return false;
    }
    ZFFI ffi;
    if (!ZFileStream_nextArray(file, sizeof(ZFFI), (ZByte *) &ffi)) {
        Zerror("Could not read dynamic library function metadata!");
        free(call);
        return false;
    }
    // TODO: Allocate type metadata or reuse types by index
    if (ffi.dynCount == ZLANG_FFI_NO_VARADIC) {
        if (ffi_prep_cif(
                call->cif,
                (ffi_abi) ffi.abi,
                ffi.argCount,
                ffi.) != FFI_OK) {
            Zerror("Could not prepare dynamic library function!");
            free(call);
            return false;
        }
    } else {
        if (ffi_prep_cif_var(
                call->cif,
                (ffi_abi) ffi.abi,
                ffi.argCount,
                ffi.dynCount,
                ffi.) != FFI_OK) {
            Zerror("Could not prepare varadic dynamic library function!");
            free(call);
            return false;
        }
    }
    if (!ZVector_push(&self->ffi, (ZULong) call)) {
        Zerror("Could not insert dynamic library function!");
        free(call);
        return false;
    }
    return true;
}

/** Cleans up all memory owned by a dynamic library. */
void ZLibrary_delete(ZLibrary *self) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->handle != NULL, "<self>'s handle was NULL!");

#ifdef ZLANG_WINDOWS

    FreeLibrary(self->handle);

#else

#ifdef ZLANG_POSIX

    dlclose(self->handle);

#endif

#endif

    self->handle = NULL;
    for (ZUInt i = 0; i < self->ffi.count; ++i) {
        ZCall *call = (ZCall *) ZVector_get(&self->ffi, i);
        free(call->cif.arg_types);
        free(call);
    }
    ZVector_delete(&self->ffi);
    for (ZUInt i = 0; i < self->types.count; ++i) {
        ffi_type *type = (ffi_type *) ZVector_get(&self->types, i);
        free(type->elements);
        free(type);
    }
    ZVector_delete(&self->types);
}
