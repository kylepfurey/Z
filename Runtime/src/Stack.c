// .c
// Z Stack Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new stack. This does not need to be deleted. */
ZBool ZStack_new(ZStack *self, ZUInt pushed) {
    Zassert(self != NULL, "<self> was NULL!");
    self->top = self->bottom;
    return ZStack_push(self, pushed);
}

/** Pushes bytes to the stack. */
ZBool ZStack_push(ZStack *self, ZUInt size) {
    Zassert(self != NULL, "<self> was NULL!");
    if (self->top + size > self->bottom + ZLANG_STACK_SIZE) {
        Zerror("Stack overflow!");
        return false;
    }
    self->top += size;
    return true;
}

/** Pops bytes from the stack. */
ZBool ZStack_pop(ZStack *self, ZUInt size) {
    Zassert(self != NULL, "<self> was NULL!");
    if (self->top - size < self->bottom) {
        Zerror("Stack underflow!");
        return false;
    }
    self->top -= size;
    return true;
}

/** Returns a pointer to the stack data at the given offset. */
void *ZStack_peek(ZStack *self, ZUInt offset) {
    Zassert(self != NULL, "<self> was NULL!");
    if (offset > (self->top - self->bottom)) {
        Zerror("Invalid stack offset!");
        return NULL;
    }
    return self->top - offset;
}

/** Returns the current size of the stack. */
ZUInt ZStack_size(const ZStack *self) {
    Zassert(self != NULL, "<self> was NULL!");
    return (ZUInt) (self->top - self->bottom);
}
