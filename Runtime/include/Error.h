// .h
// Z Error and Logging Macros
// by Kyle Furey

#ifndef ZLANG_ERROR_H
#define ZLANG_ERROR_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZLANG_DEBUG
/** Logs a message to the Z runtime when debugging. */
#define ZLog(...) do { fprintf(stdout, "Z LOG: "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); } while (false)
#else
/** Logs a message to the Z runtime when debugging. */
#define ZLog(...)
#endif

#ifdef ZLANG_DEBUG
/** Logs an error to the Z runtime when debugging. */
#define ZError(...) do { fprintf(stderr, "Z ERROR: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while (false)
#else
/** Logs an error to the Z runtime when debugging. */
#define ZError(...)
#endif

/** Returned when the Z runtime executes OK. */
#define ZLANG_OK 0

/** Returned when the Z runtime encounters an error. */
#define ZLANG_ERROR 'Z'

/** Crashes the Z runtime with the given message <msg> if <cond> is false. */
ZLANG_API void ZAssert(ZBool cond, ZString msg);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_ERROR_H
