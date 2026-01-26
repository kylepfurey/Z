// .c
// Z Program Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new Z program using a stack-allocated coroutine and file stream. */
ZBool ZProgram_new(ZProgram *self, ZCoroutine *coroutine, ZFileStream *fileStream) {
}

/** Starts an additional coroutine and sets <handle> to its index. */
ZBool ZProgram_startCoroutine(ZProgram *self, ZULong offset, ZUShort *handle) {
}

/** Stops the coroutine with <handle>. */
ZBool ZProgram_stopCoroutine(ZProgram *self, ZUShort handle) {
}

/** Loads a .zlib file into a Z program. */
ZBool ZProgram_loadFile(ZProgram *self, ZString path) {
}

/** Executes the next step in a Z program. Returns whether the program can continue. */
ZBool ZProgram_run(ZProgram *self) {
}

/** Cleans up all memory owned by a Z program. */
void ZProgram_delete(ZProgram *self) {
}
