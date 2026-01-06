// .h
// Z Byte Array Operation Functions
// by Kyle Furey

#ifndef ZLANG_BYTESTREAM_H
#define ZLANG_BYTESTREAM_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Outputs a value-sized number of bytes from a byte stream. */
#define ZBytesNextValue(byte_stream, value) ZBytesNextArray((byte_stream), sizeof(*(value)), (ZByte *) (value))

/** A handle to an array of bytes used to iterate its memory. */
typedef struct {
    /** The iterated array of bytes. */
    const ZByte *array;

    /** The index of the current byte in the array. */
    ZIndex index;

    /** The size of the array of bytes. */
    ZSize size;
} ZByteStream;

/** Initializes a .zac or .zlib program from the given array of bytes into a byte stream. */
ZLANG_API ZBool ZBytesInit(ZSize size, const ZByte *array, ZByteStream *byte_stream);

/** Outputs the current byte of a byte stream. */
ZLANG_API ZBool ZBytesCurrent(ZByteStream *byte_stream, ZByte *byte);

/** Outputs the next byte of a byte stream. */
ZLANG_API ZBool ZBytesNext(ZByteStream *byte_stream, ZByte *byte);

/** Outputs an array of bytes from a byte stream. */
ZLANG_API ZBool ZBytesNextArray(ZByteStream *byte_stream, ZSize size, ZByte *array);

/** Jumps to the given byte index in a byte stream. */
ZLANG_API ZBool ZBytesJump(ZByteStream *byte_stream, ZIndex index);

/** Returns the current byte index of a byte stream. */
ZLANG_API ZIndex ZBytesIndex(const ZByteStream *byte_stream);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_BYTESTREAM_H
