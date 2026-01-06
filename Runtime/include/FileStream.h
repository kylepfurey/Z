// .h
// Z File Operation Functions
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
    ZUInt chunk_index;

    /** The index of the current byte in the current file chunk. */
    ZUShort index;

    /** The size of the current file chunk. */
    ZUShort size;

    /** The file's handle used to iterate file chunks. */
    FILE *file;
} ZFileStream;

/** Loads a .zac or .zlib program at the given path into a file stream. */
ZLANG_API ZBool ZFileLoad(ZString path, ZFileStream *file_stream);

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZLANG_API ZBool ZFileNext(ZFileStream *file_stream, ZByte *byte);

/** Jumps to the given byte index in a file stream. */
ZLANG_API ZBool ZFileJump(ZFileStream *file_stream, ZIndex index);

/** Returns the current byte index of a file stream. */
ZLANG_API ZIndex ZFileIndex(const ZFileStream *file_stream);

/** Closes a file stream. */
ZLANG_API void ZFileClose(ZFileStream *file_stream);

#ifdef __cplusplus
}
#endif

#endif // ZLANG_FILESTREAM_H
