// .h
// Z Execution Function
// by Kyle Furey

#ifndef ZLANG_EXECUTE_H
#define ZLANG_EXECUTE_H

#include <Types.h>

/** Contains the arguments of the program. */
typedef struct {
    /** The number of arguments passed to the program. */
    ZUInt count;

    /** The arguments passed to the program as an array of strings. */
    ZString *array;
} ZArgs;

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZLANG_API ZInt Zexecute(ZString path, ZArgs args);

#endif // ZLANG_EXECUTE_H
