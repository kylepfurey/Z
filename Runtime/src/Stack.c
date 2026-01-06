// .c
// Z Stack Operation Functions
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new stack. */
ZBool ZStackInit(ZSize pushed, ZStack *stack) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    stack->top = stack->bottom;
    return ZStackPush(stack, pushed);
}

/** Pushes bytes to the stack. */
ZBool ZStackPush(ZStack *stack, ZSize size) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    if (stack->top + size > stack->bottom + ZLANG_STACK_SIZE) {
        ZError("Stack overflow!");
        return false;
    }
    memset(stack->top, 0, size);
    stack->top += size;
    return true;
}

/** Pops bytes from the stack. */
ZBool ZStackPop(ZStack *stack, ZSize size) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    if (stack->top - size < stack->bottom) {
        ZError("Stack underflow!");
        return false;
    }
    stack->top -= size;
    return true;
}

/** Returns a pointer to the stack data at the given index. */
void *ZStackGet(ZStack *stack, ZIndex index, ZIndex size) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    if (index + size >= (ZIndex) (stack->top - stack->bottom)) {
        ZError("Invalid stack index!");
        return NULL;
    }
    return stack->bottom + index;
}

/** Returns a pointer to the stack data at the given index. */
const void *ZStackGetConst(const ZStack *stack, ZIndex index, ZIndex size) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    if (index + size >= (ZIndex) (stack->top - stack->bottom)) {
        ZError("Invalid stack index!");
        return NULL;
    }
    return stack->bottom + index;
}

/** Sets the stack data at the given index. */
ZBool ZStackSet(ZStack *stack, ZIndex index, ZIndex size, const ZByte *data) {
    ZAssert(stack != NULL, "<stack> was NULL!");
    if (index + size >= (ZIndex) (stack->top - stack->bottom)) {
        ZError("Invalid stack index!");
        return false;
    }
    memmove(stack->bottom + index, data, size);
    return true;
}
