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
    ZAssert(ZStackInit(sizeof(ZInt), &stack), "Stack initialization error!");
    ZByte byte;
    ZUShort num;
    ZInt result;
    while (ZFileNext(&main, &byte)) {
        ZLog("%p - %c", (void *) (ZFileIndex(&main) - 1), byte); // TODO - ZOpcodes
        switch (byte) {
            case ZOPCODE_EXIT:
                goto exit;
            case ZOPCODE_PUSH:
                if (!ZFileNextValue(&main, &num) || !ZStackPush(&stack, num)) {
                    ZError("Runtime error!");
                    result = ZLANG_ERROR;
                    goto error;
                }
                break;
            case ZOPCODE_POP:
                if (!ZFileNextValue(&main, &num) || !ZStackPop(&stack, num)) {
                    ZError("Runtime error!");
                    result = ZLANG_ERROR;
                    goto error;
                }
                break;
            default:
                break;
        }
    }
    ZError("No exit byte!");
exit:
    result = *(ZInt *) stack.bottom;
error:
    ZFileClose(&main);
    return result;
}

/** Executes a .zac file in the given array of bytes, returning 0 or an error code from the program. */
ZInt ZExecuteBytes(ZSize size, const ZByte *array) {
    ZAssert(array != NULL, "<array> was NULL!");
    ZByteStream main;
    if (!ZBytesLoad(size, array, &main)) {
        ZError("Could not load byte array!");
        return ZLANG_ERROR;
    }
    ZStack stack;
    ZAssert(ZStackInit(sizeof(ZInt), &stack), "Stack initialization error!");
    ZByte byte;
    ZUShort num;
    ZInt result;
    while (ZBytesNext(&main, &byte)) {
        ZLog("%p - %c", (void *) (ZBytesIndex(&main) - 1), byte); // TODO - ZOpcodes
        switch (byte) {
            case ZOPCODE_EXIT:
                goto exit;
            case ZOPCODE_PUSH:
                if (!ZBytesNextValue(&main, &num) || !ZStackPush(&stack, num)) {
                    ZError("Runtime error!");
                    result = ZLANG_ERROR;
                    goto error;
                }
                break;
            case ZOPCODE_POP:
                if (!ZBytesNextValue(&main, &num) || !ZStackPop(&stack, num)) {
                    ZError("Runtime error!");
                    result = ZLANG_ERROR;
                    goto error;
                }
                break;
            default:
                break;
        }
    }
    ZError("No exit byte!");
exit:
    result = *(ZInt *) stack.bottom;
error:
    ZBytesClose(&main);
    return result;
}
