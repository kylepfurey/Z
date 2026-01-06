// .h
// Z Opcode Enum and Functions
// by Kyle Furey

#ifndef ZLANG_OPCODE_H
#define ZLANG_OPCODE_H

/** Z language runtime opcodes. */
typedef enum {
    /** Magic number for start and end of file. */
    ZOPCODE_MAGIC = 'Z',

    /** Does nothing. */
    ZOPCODE_NOOP = '\n',

    /**
     * Exits the program immediately.
     * The first 32-bit integer on the stack is always the return code.
     */
    ZOPCODE_EXIT = 'E',
} ZOpcode;

#endif // ZLANG_OPCODE_H
