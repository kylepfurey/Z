// .h
// Z Opcode Functions
// by Kyle Furey

#ifndef ZLANG_OPCODE_H
#define ZLANG_OPCODE_H

#include <Types.h>

/** Each enumerated operation code. */
enum {
    ZOPCODE_MAGIC = 'Z',
    ZOPCODE_exit = 'E',
    ZOPCODE_open = 'O',
    ZOPCODE_load = 'L',
    ZOPCODE_push = 'P',
    ZOPCODE_pop = 'p',
    ZOPCODE_move = 'M',
    ZOPCODE_set = 'S',
    ZOPCODE_get = '{',
    ZOPCODE_put = '}',
    ZOPCODE_ptr = '@',
    ZOPCODE_jump = 'J',
    ZOPCODE_hop = 'j',
    ZOPCODE_call = 'C',
    ZOPCODE_ret = 'R',
    ZOPCODE_addr = '$',
    ZOPCODE_eql = '=',
    ZOPCODE_grtr = 'G',
    ZOPCODE_flip = '!',
    ZOPCODE_if = '?',
    ZOPCODE_coro = 'A',
    ZOPCODE_bind = 'B',
    ZOPCODE_yld = 'Y',
    ZOPCODE_wait = 'W',
    ZOPCODE_cncl = 'X',
    ZOPCODE_kill = 'Z',
    ZOPCODE_inc = 'i',
    ZOPCODE_dec = 'd',
    ZOPCODE_add = '+',
    ZOPCODE_sub = '-',
    ZOPCODE_mult = '*',
    ZOPCODE_div = '/',
    ZOPCODE_mod = '%',
    ZOPCODE_and = '&',
    ZOPCODE_or = '|',
    ZOPCODE_not = '~',
    ZOPCODE_xor = '^',
    ZOPCODE_lshf = '<',
    ZOPCODE_rshf = '>',
    ZOPCODE_hash = '#',
    ZOPCODE_ffi = 'f',
    ZOPCODE_TOTAL = 40,
};

/** Each bitflag value for an operation. */
enum {
    ZOPCODE_FLAGS_WRITE_LITERAL = 1,
    ZOPCODE_FLAGS_READ_LITERAL = 2,
    ZOPCODE_FLAGS_ARG_LITERAL = 4,
    ZOPCODE_FLAGS_SIGNED = 8,
    ZOPCODE_FLAGS_FLOAT = 16,
    ZOPCODE_FLAGS_WIDTH_ONE = 32,
    ZOPCODE_FLAGS_WIDTH_TWO = 64,
    ZOPCODE_FLAGS_WIDTH_FOUR = 128,
};

#pragma pack(push, 1)

/** A single instruction for the Z runtime. */
typedef struct {
    /** The enumerated operation for this instruction. */
    ZByte code;

    /** Bitflags for this instruction. */
    ZByte flags;

    /** A stack-top offset used for writing. */
    ZUInt write;

    union {
        struct {
            /** A stack-top offset used for reading. */
            ZUInt read;

            /** A stack-top offset used for arguments. */
            ZUInt arg;
        };

        /** A literal size argument for this instruction. */
        ZULong size;
    };
} __attribute__((packed)) ZOpcode;

#pragma pack(pop)

#endif // ZLANG_OPCODE_H
