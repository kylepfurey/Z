// .h
// Z Vector Class
// by Kyle Furey

#ifndef ZLANG_VECTOR_H
#define ZLANG_VECTOR_H

#include <Types.h>

/** The default capacity for vectors. */
#define ZLANG_VECTOR_DEFAULT 8

/** A minimal dynamic array. */
typedef struct {
    /** The number of elements in the array. */
    ZUInt count;

    /** The maximum number of elements in the array before expanding. */
    ZUInt capacity;

    /** A pointer to the underlying array of elements. */
    ZULong *array;
} ZVector;

/** Initializes a new vector with the given capacity. */
ZLANG_API ZBool ZVector_new(ZVector *self, ZUInt capacity);

/** Pushes data to the back of the vector, expanding if needed. */
ZLANG_API ZBool ZVector_push(ZVector *self, ZULong data);

/** Returns the vector's data at the given index. */
ZLANG_API ZULong ZVector_get(const ZVector *self, ZUInt index);

/** Updates the vector's data at the given index. */
ZLANG_API void ZVector_set(ZVector *self, ZUInt index, ZULong data);

/** Cleans up all memory owned by a vector. */
ZLANG_API void ZVector_delete(ZVector *self);

#endif // ZLANG_VECTOR_H
