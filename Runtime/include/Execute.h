// .h
// Z Execution Function
// by Kyle Furey

#ifndef ZLANG_EXECUTE_H
#define ZLANG_EXECUTE_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZLANG_API ZInt ZExecuteFile(ZString path);

/** Executes a .zac file in the given array of bytes, returning 0 or an error code from the program. */
ZLANG_API ZInt ZExecuteBytes(ZSize size, const ZByte *array);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_EXECUTE_H
