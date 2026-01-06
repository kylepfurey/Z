// .h
// Z Stack Operation Functions
// by Kyle Furey

#ifndef ZLANG_STACK_H
#define ZLANG_STACK_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The size of a thread's stack. */
#define ZLANG_STACK_SIZE 4000000

/** A single thread's stack memory. */
typedef struct {
    /** A pointer to the base of the stack. */
    ZByte bottom[ZLANG_STACK_SIZE];

    /** A pointer to the top of the stack. */
    ZByte *top;
} ZStack;

/** Initializes a new stack. */
ZLANG_API ZBool ZStackInit(ZSize pushed, ZStack *stack);

/** Pushes bytes to the stack. */
ZLANG_API ZBool ZStackPush(ZStack *stack, ZSize size);

/** Pops bytes from the stack. */
ZLANG_API ZBool ZStackPop(ZStack *stack, ZSize size);

/** Returns a pointer to the stack data at the given index. */
ZLANG_API void *ZStackGet(ZStack *stack, ZIndex index, ZIndex size);

/** Returns a pointer to the stack data at the given index. */
ZLANG_API const void *ZStackGetConst(const ZStack *stack, ZIndex index, ZIndex size);

/** Sets the stack data at the given index. */
ZLANG_API ZBool ZStackSet(ZStack *stack, ZIndex index, ZIndex size, const ZByte *data);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_STACK_H
