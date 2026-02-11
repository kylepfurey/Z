// .c
// Z Foreign Function Interface Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new FFI call. */
ZBool ZFFI_new(ZFFI *self) {
    Zassert(self != NULL, "<self> was NULL!");
}

/** Cleans up all memory owned by an FFI call. */
void ZFFI_delete(ZFFI *self) {
    Zassert(self != NULL, "<self> was NULL!");
}
