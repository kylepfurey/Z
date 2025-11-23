// .c
// Z Error and Logging Macros
// by Kyle Furey

#include <ZLang.h>

/** Crashes the Z runtime with the given message <msg> if <cond> is false. */
void ZAssert(ZBool cond, ZString msg) {
    if (!cond) {
#ifdef ZLANG_DEBUG
        fprintf(stderr, "Z ASSERTION FAILED: ");
        fprintf(stderr, msg);
        fprintf(stderr, "\n");
#endif
        exit(ZLANG_ERROR);
    }
}
