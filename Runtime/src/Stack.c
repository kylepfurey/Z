// .c
// Z Stack Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new stack. This does not need to be deleted. */
ZBool ZStack_new(ZStack *self, ZUInt pushed) {
    ZAssert(self != NULL, "<self> was NULL!");
    self->top = self->bottom;
    return ZStack_push(self, pushed);
}

/** Pushes bytes to the stack. */
ZBool ZStack_push(ZStack *self, ZUInt size) {
    ZAssert(self != NULL, "<self> was NULL!");
    if (self->top + size > self->bottom + ZLANG_STACK_SIZE) {
        ZError("Stack overflow!");
        return false;
    }
    memset(self->top, 0, size);
    self->top += size;
    return true;
}

/** Pops bytes from the stack. */
ZBool ZStack_pop(ZStack *self, ZUInt size) {
    ZAssert(self != NULL, "<self> was NULL!");
    if (self->top - size < self->bottom) {
        ZError("Stack underflow!");
        return false;
    }
    self->top -= size;
    return true;
}

/** Returns a pointer to the stack data at the given offset. */
void *ZStack_peek(ZStack *self, ZUInt offset) {
    ZAssert(self != NULL, "<self> was NULL!");
    if (offset > (self->top - self->bottom)) {
        ZError("Invalid stack offset!");
        return NULL;
    }
    return self->top - offset;
}

/** Returns the current size of the stack. */
ZUInt ZStack_size(const ZStack *self) {
    ZAssert(self != NULL, "<self> was NULL!");
    return (ZUInt) (self->top - self->bottom);
}
