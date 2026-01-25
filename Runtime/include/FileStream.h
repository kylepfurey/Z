// .h
// Z File Stream Class
// by Kyle Furey

#ifndef ZLANG_FILESTREAM_H
#define ZLANG_FILESTREAM_H

#include <Types.h>
#ifdef __cplusplus
extern "C" {
#endif

/** The size of a single file chunk loaded into memory. */
#define ZLANG_CHUNK_SIZE 1024

/** A handle to a file used to iterate its memory in chunks. */
typedef struct {
    /** The file chunk buffer. */
    ZByte chunk[ZLANG_CHUNK_SIZE];

    /** The index of the current file chunk. */
    ZUInt chunkIndex;

    /** The size of the current file chunk. */
    ZUShort chunkSize;

    /** The index of the current byte in the current file chunk. */
    ZUShort byteIndex;

    /** The global offset of this file in virtual memory. */
    ZULong globalOffset;

    /** The size of this file's binary. */
    ZULong fileSize;

    /** The file's handle used to iterate file chunks. */
    FILE *file;
} ZFileStream;

/** Loads a .zac or .zlib program at the given path into a file stream. */
ZLANG_API ZBool ZFileStream_new(ZFileStream *self, ZString path, ZULong offset);

/** Outputs the current byte of a file stream. */
ZLANG_API ZBool ZFileStream_current(ZFileStream *self, ZByte *byte);

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZLANG_API ZBool ZFileStream_nextByte(ZFileStream *self, ZByte *byte);

/** Outputs an array of bytes from a file stream, iterating chunks when needed. */
ZLANG_API ZBool ZFileStream_nextArray(ZFileStream *self, ZUInt size, ZByte *array);

/** Jumps to the given byte index in a file stream. */
ZLANG_API ZBool ZFileStream_jump(ZFileStream *self, ZULong index);

/** Returns the current byte index of a file stream. */
ZLANG_API ZULong ZFileStream_index(const ZFileStream *self);

/** Closes a file stream. */
ZLANG_API void ZFileStream_delete(ZFileStream *self);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_FILESTREAM_H
