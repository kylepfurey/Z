// .h
// Z Execution Function
// by Kyle Furey

#ifndef ZLANG_EXECUTE_H
#define ZLANG_EXECUTE_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Executes the given .zac file, returning 0 or an error code from the program. */
ZLANG_API ZInt ZExecute(ZString path);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_EXECUTE_H
