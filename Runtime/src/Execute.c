// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <ZLang.h>

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZInt Zexecute(ZString path, ZArgs args) {
    Zassert(path != NULL, "<path> was NULL!");
    ZLong length = (ZLong) strlen(path);
    if (length <= 0) {
        Zerror("Invalid path!");
        return ZLANG_ERROR;
    }
    for (--length; length >= 0; --length) {
        if (path[length] == '.') {
            ZString extension = path + length + 1;
            if (tolower(extension[0]) == 'z' &&
                tolower(extension[1]) == 'a' &&
                tolower(extension[2]) == 'c') {
                break;
            }
            Zerror("Invalid executable file extension!");
            return ZLANG_ERROR;
        }
        if (length <= 0) {
            Zerror("Cannot execute a directory!");
            return ZLANG_ERROR;
        }
    }
    ZCoroutine mainCoroutine;
    if (!ZCoroutine_new(&mainCoroutine)) {
        Zerror("Could not start main coroutine!");
        return ZLANG_ERROR;
    }
    ZArgs *stackArgs = (ZArgs *) ZStack_peek(&mainCoroutine.stack, sizeof(ZArgs));
    if (stackArgs == NULL) {
        Zerror("Could not initialize arguments!");
        return ZLANG_ERROR;
    }
    *stackArgs = args;
    ZFileStream mainFileStream;
    if (!ZFileStream_new(&mainFileStream, path, 0)) {
        Zerror("Could not load executable!");
        return ZLANG_ERROR;
    }
    ZProgram mainProgram;
    if (!ZProgram_new(&mainProgram, &mainCoroutine, &mainFileStream)) {
        Zerror("Failed to start program!");
        return ZLANG_ERROR;
    }
    while (ZProgram_run(&mainProgram)) {
    }
    ZProgram_delete(&mainProgram);
    return *(ZInt *) mainCoroutine.stack.bottom;
}
