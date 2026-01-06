// .h
// Z Byte Array Operation Functions
// by Kyle Furey

#ifndef ZLANG_BYTESTREAM_H
#define ZLANG_BYTESTREAM_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** A handle to an array of bytes used to iterate its memory. */
typedef struct {
    /** The iterated array of bytes. */
    const ZByte *array;

    /** The index of the current byte in the array. */
    ZIndex index;

    /** The size of the array of bytes. */
    ZSize size;
} ZByteStream;

/** Loads a .zac or .zlib program from the given array of bytes into a byte stream. */
ZLANG_API ZBool ZBytesLoad(ZSize size, const ZByte *array, ZByteStream *byte_stream);

/** Outputs the next byte of a byte stream. */
ZLANG_API ZBool ZBytesNext(ZByteStream *byte_stream, ZByte *byte);

/** Jumps to the given byte index in a byte stream. */
ZLANG_API ZBool ZBytesJump(ZByteStream *byte_stream, ZIndex index);

/** Returns the current byte index of a byte stream. */
ZLANG_API ZIndex ZBytesIndex(const ZByteStream *byte_stream);

/** Closes a byte stream. */
ZLANG_API void ZBytesClose(ZByteStream *byte_stream);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_BYTESTREAM_H
