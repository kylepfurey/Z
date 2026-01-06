// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <ZLang.h>

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZInt ZExecuteFile(ZString path) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZFileStream main;
    if (!ZFileLoad(path, &main)) {
        ZError("Could not load file!");
        return ZLANG_ERROR;
    }
    ZStack stack;
    if (!ZStackInit(sizeof(ZInt), &stack)) {
        ZAssert(false, "Stack initialization error!");
    }
    while (ZProcessFileOpcode(&main, &stack)) {
    }
    ZFileClose(&main);
    return *(ZInt *) stack.bottom;
}

/** Executes a .zac file in the given array of bytes, returning 0 or an error code from the program. */
ZInt ZExecuteBytes(ZSize size, const ZByte *array) {
    ZAssert(array != NULL, "<array> was NULL!");
    ZByteStream main;
    if (!ZBytesInit(size, array, &main)) {
        ZError("Could not initialize byte array!");
        return ZLANG_ERROR;
    }
    ZStack stack;
    if (!ZStackInit(sizeof(ZInt), &stack)) {
        ZAssert(false, "Stack initialization error!");
    }
    while (ZProcessBytesOpcode(&main, &stack)) {
    }
    return *(ZInt *) stack.bottom;
}
