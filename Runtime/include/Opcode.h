// .h
// Z Opcode Structure and Functions
// by Kyle Furey

#ifndef ZLANG_OPCODE_H
#define ZLANG_OPCODE_H

#include <Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** The values of each instruction bytecode. */
typedef enum {
    /** The magic number for start and end of a file. */
    ZOPCODE_MAGIC = 'Z',

    /**
     * Ends the program or kills the current coroutine immediately.
     * The return value of main() will be the program's exit code.
     */
    ZOPCODE_EXIT = 'E',
} ZOpcode;

/** A single instruction in the .zac file. */
typedef struct {
    /** The bytecode that defines what to do in this instruction. */
    ZByte code;

    /** Bitflags detailing this instruction's operation. */
    ZByte flags;

    /** The offset from the top of the stack containing the first argument. */
    ZUShort arg;

    union {
        /** A value containing a literal size. */
        ZUInt size;

        struct {
            /** The offset from the top of the stack containing the left operand. */
            ZUShort left;

            /** The offset from the top of the stack containing the right operand. */
            ZUShort right;
        };
    };
} ZInstruction;

#ifdef __cplusplus
}
#endif

#endif // ZLANG_OPCODE_H
