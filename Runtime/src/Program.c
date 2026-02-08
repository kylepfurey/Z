// .c
// Z Program Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new Z program using a stack-allocated coroutine and file stream. */
ZBool ZProgram_new(ZProgram *self, ZCoroutine *coroutine, ZFileStream *fileStream) {
}

/** Executes the next step in a Z program. Returns whether the program can continue. */
ZBool ZProgram_run(ZProgram *self) {
}

/** Cleans up all memory owned by a Z program. */
void ZProgram_delete(ZProgram *self) {
}
