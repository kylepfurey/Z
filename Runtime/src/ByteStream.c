// .c
// Z Byte Array Operation Functions
// by Kyle Furey

#include <ZLang.h>

/** Loads a .zac or .zlib program from the given array of bytes into a byte stream. */
ZBool ZBytesLoad(ZSize size, const ZByte *array, ZByteStream *byte_stream) {
    ZAssert(array != NULL, "<path> was NULL!");
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    if (size == 0 || array[0] != ZOPCODE_MAGIC) {
        ZError("Byte array does not start with the Z byte!");
        return false;
    }
    if (size <= 1 || array[size - 1] != ZOPCODE_MAGIC) {
        ZError("Byte array does not end with the Z byte!");
        return false;
    }
    *byte_stream = (ZByteStream){
        array,
        1,
        size,
    };
    return true;
}

/** Outputs the next byte of a byte stream. */
ZBool ZBytesNext(ZByteStream *byte_stream, ZByte *byte) {
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    ZAssert(byte_stream->array != NULL, "<byte_stream>'s array was NULL!");
    ZAssert(byte != NULL, "<byte> was NULL!");
    if (byte_stream->index >= byte_stream->size) {
        return false;
    }
    *byte = byte_stream->array[byte_stream->index++];
    return byte_stream->index < byte_stream->size;
}

/** Jumps to the given byte index in a byte stream. */
ZBool ZBytesJump(ZByteStream *byte_stream, ZIndex index) {
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    ZAssert(byte_stream->array != NULL, "<byte_stream>'s array was NULL!");
    byte_stream->index = index;
    return index < byte_stream->size;
}

/** Returns the current byte index of a byte stream. */
ZIndex ZBytesIndex(const ZByteStream *byte_stream) {
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    return byte_stream->index;
}

/** Closes a byte stream. */
void ZBytesClose(ZByteStream *byte_stream) {
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    ZAssert(byte_stream->array != NULL, "<byte_stream>'s array was NULL!");
    byte_stream->array = NULL;
}
