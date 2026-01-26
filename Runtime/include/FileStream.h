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
ZLANG_API ZBool ZFileStream_new(ZFileStream *self, ZString path, ZULong globalOffset);

/** Outputs the current byte of a file stream. */
ZLANG_API ZBool ZFileStream_currentByte(ZFileStream *self, ZByte *byte);

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZLANG_API ZBool ZFileStream_nextByte(ZFileStream *self, ZByte *byte);

/** Outputs an array of bytes from a file stream, iterating chunks when needed. */
ZLANG_API ZBool ZFileStream_nextArray(ZFileStream *self, ZUInt size, ZByte *array);

/** Jumps to the given local offset in a file stream. */
ZLANG_API ZBool ZFileStream_jumpLocal(ZFileStream *self, ZULong localOffset);

/** Returns the current local offset of a file stream. */
ZLANG_API ZULong ZFileStream_localOffset(const ZFileStream *self);

/** Returns the current global offset of a file stream. */
ZLANG_API ZULong ZFileStream_globalOffset(const ZFileStream *self);

/** Returns whether a global offset is in range of a file stream. */
ZLANG_API ZBool ZFileStream_inRange(const ZFileStream *self, ZULong globalOffset);

/** Closes a file stream. */
ZLANG_API void ZFileStream_delete(ZFileStream *self);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_FILESTREAM_H
