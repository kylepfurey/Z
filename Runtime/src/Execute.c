// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <ZLang.h>

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZInt ZExecuteFile(ZString path) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZInt result = 0; // TODO - stack
    ZFileStream main;
    if (!ZFileLoad(path, &main)) {
        ZError("Could not load file!");
        return ZLANG_ERROR;
    }
    ZByte byte;
    while (ZFileNext(&main, &byte)) {
        if (byte == ZOPCODE_NOOP) {
            continue;
        }
        if (byte == ZOPCODE_EXIT) {
            break;
        }
        ZLog("%p - %c", (ZPtr) (ZFileIndex(&main) - 1), byte);
    }
    ZFileClose(&main);
    return result;
}

/** Executes a .zac file in the given array of bytes, returning 0 or an error code from the program. */
ZInt ZExecuteBytes(ZSize size, const ZByte *array) {
    ZAssert(array != NULL, "<array> was NULL!");
    ZInt result = 0; // TODO - stack
    ZByteStream main;
    if (!ZBytesLoad(size, array, &main)) {
        ZError("Could not load byte array!");
        return ZLANG_ERROR;
    }
    ZByte byte;
    while (ZBytesNext(&main, &byte)) {
        if (byte == ZOPCODE_NOOP) {
            continue;
        }
        if (byte == ZOPCODE_EXIT) {
            break;
        }
        ZLog("%p - %c", (ZPtr) (ZBytesIndex(&main) - 1), byte);
    }
    ZBytesClose(&main);
    return result;
}
