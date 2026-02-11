// .h
// Z Execution Function
// by Kyle Furey

#ifndef ZLANG_EXECUTE_H
#define ZLANG_EXECUTE_H

#include <Types.h>

/** Executes a .zac file at the given path, returning 0 or an error code from the program. */
ZLANG_API ZInt Zexecute(ZString path, ZUInt argc, const ZString argv[]);

#endif // ZLANG_EXECUTE_H
