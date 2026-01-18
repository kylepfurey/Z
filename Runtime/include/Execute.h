// .h
// Z Execution Function
// by Kyle Furey

#ifndef ZLANG_EXECUTE_H
#define ZLANG_EXECUTE_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Contains the arguments of the program. */
typedef struct {
    /** The number of arguments passed to the program. */
    ZUInt argc;

    /** The arguments passed to the program as an array of strings. */
    ZString *argv;
} ZArgs;

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZLANG_API ZInt ZExecute(ZString path, ZArgs args);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_EXECUTE_H
