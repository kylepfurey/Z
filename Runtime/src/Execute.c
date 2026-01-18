// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <ZLang.h>

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZInt ZExecute(ZString path, ZArgs args) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZFileStream main;
    if (!ZFileLoad(path, &main)) {
        ZError("Could not load file!");
        return ZLANG_ERROR;
    }
    ZStack stack;
    ZAssert(ZStackInit(sizeof(ZInt) + sizeof(ZArgs), &stack), "Stack initialization error!");
    *(ZArgs *) ZStackPeek(&stack, sizeof(ZArgs)) = args;
    ZFileClose(&main);
    return *(ZInt *) stack.bottom;
}
