// .h
// Z Opcode Enum and Functions
// by Kyle Furey

#ifndef ZLANG_OPCODE_H
#define ZLANG_OPCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/** Z language runtime opcodes. */
typedef enum {
    /** Magic number for start and end of file. */
    ZOPCODE_MAGIC = 'Z',

    /**
     * Exits the program immediately.
     * The first 32-bit integer on the stack is always the return code.
     */
    ZOPCODE_EXIT = 'E',

    /** Pushes data to the stack. */
    ZOPCODE_PUSH = 'P',

    /** Pops data from the stack. */
    ZOPCODE_POP = 'p',
} ZOpcode;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_OPCODE_H
