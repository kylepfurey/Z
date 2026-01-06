// .c
// Z Opcode Enum and Functions
// by Kyle Furey

#include <ZLang.h>

/** Processes a Z opcode in a file stream. */
ZBool ZProcessFileOpcode(ZFileStream *file_stream, ZStack *stack) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(stack != NULL, "<stack> was NULL!");
    ZByte byte;
    ZUShort num;
    if (!ZFileNext(file_stream, &byte)) {
        return false;
    }
    ZLog("%p - %c", (void *) (ZFileIndex(file_stream) - 1), byte);
    switch (byte) {
        case ZOPCODE_EXIT:
            return false;
        case ZOPCODE_PUSH:
            if (!ZFileNextValue(file_stream, &num) || !ZStackPush(stack, num)) {
                ZError("Runtime error!");
                return false;
            }
            break;
        case ZOPCODE_POP:
            if (!ZFileNextValue(file_stream, &num) || !ZStackPop(stack, num)) {
                ZError("Runtime error!");
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

/** Processes a Z opcode in a file stream. */
ZBool ZProcessBytesOpcode(ZByteStream *byte_stream, ZStack *stack) {
    ZAssert(byte_stream != NULL, "<byte_stream> was NULL!");
    ZAssert(stack != NULL, "<stack> was NULL!");
    ZByte byte;
    ZUShort num;
    if (!ZBytesNext(byte_stream, &byte)) {
        return false;
    }
    ZLog("%p - %c", (void *) (ZBytesIndex(byte_stream) - 1), byte);
    switch (byte) {
        case ZOPCODE_EXIT:
            return false;
        case ZOPCODE_PUSH:
            if (!ZBytesNextValue(byte_stream, &num) || !ZStackPush(stack, num)) {
                ZError("Runtime error!");
                return false;
            }
            break;
        case ZOPCODE_POP:
            if (!ZBytesNextValue(byte_stream, &num) || !ZStackPop(stack, num)) {
                ZError("Runtime error!");
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}
