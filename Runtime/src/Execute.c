// .c
// Z Runtime Execution Function
// by Kyle Furey

#include <Execute.h>
#include <Error.h>

/** Executes the given .zac file, returning 0 or an error code from the program. */
ZInt32 ZExecute(ZString path) {
    ZAssert(path != NULL, "ZExecute() - <path> was NULL!");
    return 0;
}
