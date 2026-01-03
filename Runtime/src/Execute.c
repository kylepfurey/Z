// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <ZLang.h>

/** Executes the given .zac file, returning 0 or an error code from the program. */
ZInt ZExecute(ZString path) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZFileStream main;
    if (!ZFileLoad(path, &main)) {
        ZError("Could not load file!");
        return ZLANG_ERROR;
    }
    ZByte byte;
    while (ZFileNext(&main, &byte)) {
        ZLog("%p - %c", (ZPtr) (ZFileIndex(&main) - 1), byte);
    }
    ZFileClose(&main);
    return 0;
}
