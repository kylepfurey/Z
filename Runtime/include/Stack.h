// .h
// Z Stack Class
// by Kyle Furey

#ifndef ZLANG_STACK_H
#define ZLANG_STACK_H

#include <Types.h>

/** The size of a thread's stack. */
#define ZLANG_STACK_SIZE 4000000

/** A single thread's stack memory. */
typedef struct {
    /** A pointer to the base of this stack. */
    ZByte bottom[ZLANG_STACK_SIZE];

    /** A pointer to the top of this stack. */
    ZByte *top;
} ZStack;

/** Initializes a new stack. This does not need to be deleted. */
ZLANG_API ZBool ZStack_new(ZStack *self, ZUInt pushed);

/** Pushes bytes to the stack. */
ZLANG_API ZBool ZStack_push(ZStack *self, ZUInt size);

/** Pops bytes from the stack. */
ZLANG_API ZBool ZStack_pop(ZStack *self, ZUInt size);

/** Returns a pointer to the stack data at the given offset. */
ZLANG_API void *ZStack_peek(ZStack *self, ZUInt offset);

/** Returns the current size of the stack. */
ZLANG_API ZUInt ZStack_size(const ZStack *self);

#endif // ZLANG_STACK_H
