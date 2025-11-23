// .h
// Z Type Declarations
// by Kyle Furey

#ifndef ZLANG_TYPES_H
#define ZLANG_TYPES_H

#include <External.h>
#include <Export.h>

#ifdef __cplusplus
extern "C" {
#endif

/** A true or false boolean value. */
typedef bool ZBool;

/** An 8-bit signed integral number. */
typedef int8_t ZInt8;

/** An 8-bit unsigned integral number. */
typedef uint8_t ZUInt8;

/** A 16-bit signed integral number. */
typedef int16_t ZInt16;

/** A 16-bit unsigned integral number. */
typedef uint16_t ZUInt16;

/** A 32-bit signed integral number. */
typedef int32_t ZInt32;

/** A 32-bit unsigned integral number. */
typedef uint32_t ZUInt32;

/** A 64-bit signed integral number. */
typedef int64_t ZInt64;

/** A 64-bit unsigned integral number. */
typedef uint64_t ZUInt64;

/** An unsigned integral number that can represent any size. */
typedef size_t ZSize;

/** An unsigned integral number that represents the index of some data. */
typedef ZSize ZIndex;

/** A signed integral number that represents the difference between some data. */
typedef ptrdiff_t ZDiff;

/** An unsigned integral number that represents the address of some data. */
typedef uintptr_t ZPtr;

/** A 32-bit floating-point decimal number. */
typedef float ZFloat;

/** A 64-bit floating-point decimal number. */
typedef double ZDouble;

/** A byte representing a single symbol of text. */
typedef char ZChar;

/** A null-terminated sequence of characters representing text. */
typedef const ZChar *ZString;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_TYPES_H
