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
} ZOpcode;

/** Processes a Z opcode in a file stream. */
ZLANG_API ZBool ZProcessFileOpcode(ZFileStream *file_stream, ZStack *stack);

/** Processes a Z opcode in a file stream. */
ZLANG_API ZBool ZProcessBytesOpcode(ZByteStream *byte_stream, ZStack *stack);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_OPCODE_H
