// .h
// Z Dynamic Library Class
// by Kyle Furey

#ifndef ZLANG_LIBRARY_H
#define ZLANG_LIBRARY_H

#include <FileStream.h>

/** Denotes that an FFI function is not a varadic function. */
#define ZLANG_FFI_NO_VARADIC UINT_MAX

/** Each enumerated primitive type. */
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

    /** A vector of pointers to foreign function types. */
    ZVector types;
} ZLibrary;

/** Data for calling a foreign function. */
typedef struct {
    /** The foreign function to call. */
    ZFunc func;

    /** The foreign function call's interface. */
    ffi_cif cif;
} ZCall;

#pragma pack(push, 1)

/** Metadata for a foreign function interface call. */
typedef struct {
    /** The ABI of this foreign function call. */
    ZUInt abi;

    /** The total number of typed args. */
    ZUInt argCount;

    /** The total number of dynamic args. ZLANG_FFI_NO_VARADIC ignores this. */
    ZUInt dynCount;

    /** The local address of the return type. */
    ZULong returnType;
} __attribute__((packed)) ZFFI;

/** Metadata for a foreign type. */
typedef struct {
    /** The size in bytes of this type. */
    ZULong size;

    /** The alignment in bytes of this type. */
    ZUShort alignment;

    /** The ABI category of this type. */
    ZUShort type;

    /** The total number of element types. */
    ZUInt elemCount;
} __attribute__((packed)) ZType;

#pragma pack(pop)

/** Initializes a new dynamic library. */
ZLANG_API ZBool ZLibrary_new(ZLibrary *self, ZString name);

/** Returns a function pointer from a dynamic library via its name. */
ZLANG_API ZFunc ZLibrary_find(ZLibrary *self, ZString func);

/**
 * Calls a foreign function with the given index.
 * If this is the first call, this prepares the function instead.
 */
ZLANG_API ZBool ZLibrary_call(ZLibrary *self, ZFileStream *file, ZUInt index);

/** Cleans up all memory owned by a dynamic library. */
ZLANG_API void ZLibrary_delete(ZLibrary *self);

#endif // ZLANG_LIBRARY_H
