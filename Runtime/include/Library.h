// .h
// Z Dynamic Library Class
// by Kyle Furey

#ifndef ZLANG_LIBRARY_H
#define ZLANG_LIBRARY_H

#include <Vector.h>
#include <Stack.h>

/** Denotes that an FFI function is not a varadic function. */
#define ZLANG_CALL_NO_VARADIC UINT_MAX

/** Denotes that an FFI function uses the default OS ABI. */
#define ZLANG_DEFAULT_ABI UINT_MAX

/** Denotes at runtime that an FFI call is for libc. */
#define ZLANG_FFI_LIBC UINT_MAX

/**
 * Each enumerated primitive type.
 * Custom struct types follow at and after ZLANG_TYPE_STRUCT.
 */
enum {
    ZLANG_TYPE_VOID = 0,
    ZLANG_TYPE_BYTE = 1,
    ZLANG_TYPE_SBYTE = 2,
    ZLANG_TYPE_USHORT = 3,
    ZLANG_TYPE_SHORT = 4,
    ZLANG_TYPE_UINT = 5,
    ZLANG_TYPE_INT = 6,
    ZLANG_TYPE_ULONG = 7,
    ZLANG_TYPE_LONG = 8,
    ZLANG_TYPE_FLOAT = 9,
    ZLANG_TYPE_DOUBLE = 10,
    ZLANG_TYPE_PTR = 11,
    ZLANG_TYPE_DECIMAL = 12,
    ZLANG_TYPE_STRUCT = 13, // >= 13
};

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

/** Data for a foreign function interface. */
typedef struct {
    /** The interface of this foreign function. cif.arg_types must be freed! */
    ffi_cif cif;

    /** A pointer to the foreign function. */
    ZFunc func;

    /**
     * Cached data for the function signature.
     * [0] = Return Stack Offset
     * [1] = Argument Count
     * [...] = Argument Stack Offset
     * This must be freed!
     */
    ZUInt *signature;
} ZFFI;

/** Data for a static type. */
typedef ffi_type ZType;

#pragma pack(push, 1)

/** Metadata for a foreign function interface call. */
typedef struct {
    /** The ABI of this foreign function call. ZLANG_DEFAULT_ABI is for default ABI. */
    ZUInt abi;

    /** The total number of typed arguments. Argument type indicies follow this structure. */
    ZUInt fixedArgs;

    /** The total number of varadic arguments. ZLANG_CALL_NO_VARADIC ignores this. */
    ZUInt varArgs;

    /** The type index of the return type. */
    ZUInt returnType;
} __attribute__((packed)) ZCall;

#pragma pack(pop)

/** Initializes a new dynamic library. "libc" loads the standard library. */
ZLANG_API ZBool ZLibrary_new(ZLibrary *self, ZString name);

/** Returns a function pointer from a dynamic library via its name. */
ZLANG_API ZFunc ZLibrary_find(ZLibrary *self, ZString name);

/** Binds a new foreign function to the library. */
ZLANG_API ZBool ZLibrary_bind(
    ZLibrary *self,
    ZString name,
    ZUInt abi,
    ZUInt fixedArgs,
    ZUInt varArgs,
    ZType *returnType,
    ZType *argTypes[]
);

/** Invokes the foreign function stored in the library with the given index. */
ZLANG_API ZBool ZLibrary_call(ZLibrary *self, ZUInt index, ZStack *stack);

/** Cleans up all memory owned by a dynamic library. */
ZLANG_API void ZLibrary_delete(ZLibrary *self);

#endif // ZLANG_LIBRARY_H
