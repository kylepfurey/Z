// .c
// Z File Stream Class
// by Kyle Furey

#include <ZLang.h>

/** Initializes a new file stream. */
ZBool ZFileStream_new(ZFileStream *self, ZString path, ZULong globalOffset) {
    Zassert(path != NULL, "<path> was NULL!");
    Zassert(self != NULL, "<self> was NULL!");
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        Zerror("File not found!");
        return false;
    }
    self->chunkSize = fread(self->chunk, 1, ZLANG_CHUNK_SIZE, file);
    if (self->chunk[0] != ZOPCODE_MAGIC) {
        fclose(file);
        Zerror("File does not start with the Z byte!");
        return false;
    }
    if (self->chunkSize <= 1) {
        fclose(file);
        Zerror(
            self->chunkSize == 0 ?
            "File does not start with the Z byte!" :
            "File does not end with the Z byte!"
        );
        return false;
    }
    if (fseek(file, -1, SEEK_END) != 0 || fgetc(file) != ZOPCODE_MAGIC) {
        fclose(file);
        Zerror("File does not end with the Z byte!");
        return false;
    }
    self->globalOffset = globalOffset;
    self->chunkIndex = 0;
    self->byteIndex = 1;
    fseek(file, 0, SEEK_END);
    self->fileSize = ftell(file);
    fseek(file, ZLANG_CHUNK_SIZE, SEEK_SET);
    self->file = file;
    return true;
}

/** Outputs the current byte of a file stream. */
ZBool ZFileStream_currentByte(ZFileStream *self, ZByte *byte) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->file != NULL, "<self>'s FILE handle was NULL!");
    Zassert(byte != NULL, "<byte> was NULL!");
    if (self->byteIndex >= self->chunkSize) {
        return false;
    }
    *byte = self->chunk[self->byteIndex];
    return true;
}

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZBool ZFileStream_nextByte(ZFileStream *self, ZByte *byte) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->file != NULL, "<self>'s FILE handle was NULL!");
    Zassert(byte != NULL, "<byte> was NULL!");
    if (self->byteIndex >= self->chunkSize) {
        return false;
    }
    *byte = self->chunk[self->byteIndex++];
    if (self->byteIndex == self->chunkSize) {
        self->byteIndex = 0;
        ++self->chunkIndex;
        self->chunkSize = fread(self->chunk, 1, ZLANG_CHUNK_SIZE, self->file);
        if (self->chunkSize == 0) {
            return false;
        }
    }
    return true;
}

/** Outputs an array of bytes from a file stream, iterating chunks when needed. */
ZBool ZFileStream_nextArray(ZFileStream *self, ZUInt size, ZByte *array) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->file != NULL, "<self>'s FILE handle was NULL!");
    Zassert(array != NULL, "<array> was NULL!");
    if (ZLANG_LITTLE_ENDIAN) {
        for (; size > 0; --size) {
            if (!ZFileStream_nextByte(self, array++)) {
                return false;
            }
        }
    } else {
        array += size;
        for (; size > 0; --size) {
            if (!ZFileStream_nextByte(self, --array)) {
                return false;
            }
        }
    }
    return true;
}

/** Jumps to the given byte index in a file stream. */
ZBool ZFileStream_jumpLocal(ZFileStream *self, ZULong localOffset) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->file != NULL, "<self>'s FILE handle was NULL!");
    ZUInt chunk = (localOffset / ZLANG_CHUNK_SIZE) * ZLANG_CHUNK_SIZE;
    if (self->chunkIndex != chunk) {
        self->chunkIndex = chunk;
        fseek(self->file, chunk, SEEK_SET);
        self->chunkSize = fread(self->chunk, 1, ZLANG_CHUNK_SIZE, self->file);
    }
    self->byteIndex = localOffset % ZLANG_CHUNK_SIZE;
    return self->byteIndex < self->chunkSize;
}

/** Returns the current byte index of a file stream. */
ZULong ZFileStream_localOffset(const ZFileStream *self) {
    Zassert(self != NULL, "<self> was NULL!");
    return (self->chunkIndex * ZLANG_CHUNK_SIZE) + self->byteIndex;
}

/** Returns the current global offset of a file stream. */
ZULong ZFileStream_globalOffset(const ZFileStream *self) {
    Zassert(self != NULL, "<self> was NULL!");
    return ZFileStream_localOffset(self) + self->globalOffset;
}

/** Returns whether a global offset is in range of a file stream. */
ZBool ZFileStream_inRange(const ZFileStream *self, ZULong globalOffset) {
    Zassert(self != NULL, "<self> was NULL!");
    return globalOffset >= self->globalOffset && globalOffset < self->globalOffset + self->fileSize;
}

/** Cleans up all memory owned by a file stream. */
void ZFileStream_delete(ZFileStream *self) {
    Zassert(self != NULL, "<self> was NULL!");
    Zassert(self->file != NULL, "<self>'s FILE handle was NULL!");
    fclose(self->file);
    self->file = NULL;
}
