// .c
// Z File Stream Class
// by Kyle Furey

#include <ZLang.h>

/** Loads a .zac or .zlib program at the given path into a file stream. */
ZBool ZFileStream_new(ZFileStream *self, ZString path, ZULong offset) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZAssert(self != NULL, "<self> was NULL!");
    ZLong length = (ZLong) strlen(path);
    if (length <= 0) {
        ZError("Invalid path!");
        return false;
    }
    for (--length; length >= 0; --length) {
        if (path[length] == '.') {
            ZString extension = path + length + 1;
            if (tolower(extension[0]) == 'z') {
                switch (tolower(extension[1])) {
                    case 'a':
                        if (tolower(extension[2]) == 'c') {
                            goto success;
                        }
                        break;
                    case 'l':
                        if (tolower(extension[2]) == 'i' &&
                            tolower(extension[3]) == 'b') {
                            goto success;
                        }
                        break;
                    default:
                        break;
                }
                ZError("Invalid file extension!");
                return false;
            }
        }
        if (length == 0) {
            ZError("Cannot execute a directory!");
            return false;
        }
    }
success:
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        ZError("File not found!");
        return false;
    }
    self->chunkSize = fread(self->chunk, 1, ZLANG_CHUNK_SIZE, file);
    if (self->chunk[0] != ZOPCODE_MAGIC) {
        fclose(file);
        ZError("File does not start with the Z byte!");
        return false;
    }
    if (self->chunkSize <= 1) {
        fclose(file);
        ZError(
            self->chunkSize == 0 ?
            "File does not start with the Z byte!" :
            "File does not end with the Z byte!"
        );
        return false;
    }
    if (fseek(file, -1, SEEK_END) != 0 || fgetc(file) != ZOPCODE_MAGIC) {
        fclose(file);
        ZError("File does not end with the Z byte!");
        return false;
    }
    fseek(file, 0, SEEK_END);
    self->fileSize = ftell(file);
    fseek(file, ZLANG_CHUNK_SIZE, SEEK_SET);
    self->byteIndex = 1;
    self->chunkIndex = 0;
    self->globalOffset = offset;
    self->file = file;
    return true;
}

/** Outputs the current byte of a file stream. */
ZBool ZFileStream_current(ZFileStream *self, ZByte *byte) {
    ZAssert(self != NULL, "<self> was NULL!");
    ZAssert(self->file != NULL, "<self>'s FILE handle was NULL!");
    ZAssert(byte != NULL, "<byte> was NULL!");
    if (self->byteIndex >= self->chunkSize) {
        return false;
    }
    *byte = self->chunk[self->byteIndex];
    return true;
}

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZBool ZFileStream_nextByte(ZFileStream *self, ZByte *byte) {
    ZAssert(self != NULL, "<self> was NULL!");
    ZAssert(self->file != NULL, "<self>'s FILE handle was NULL!");
    ZAssert(byte != NULL, "<byte> was NULL!");
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
    ZAssert(self != NULL, "<self> was NULL!");
    ZAssert(self->file != NULL, "<self>'s FILE handle was NULL!");
    ZAssert(array != NULL, "<array> was NULL!");
    ZInt endian = 1;
    if (*(ZByte *) &endian == 1) {
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
ZBool ZFileStream_jump(ZFileStream *self, ZULong index) {
    ZAssert(self != NULL, "<self> was NULL!");
    ZAssert(self->file != NULL, "<self>'s FILE handle was NULL!");
    ZUInt chunk = (index / ZLANG_CHUNK_SIZE) * ZLANG_CHUNK_SIZE;
    if (self->chunkIndex != chunk) {
        self->chunkIndex = chunk;
        fseek(self->file, chunk, SEEK_SET);
        self->chunkSize = fread(self->chunk, 1, ZLANG_CHUNK_SIZE, self->file);
    }
    self->byteIndex = index % ZLANG_CHUNK_SIZE;
    return self->byteIndex < self->chunkSize;
}

/** Returns the current byte index of a file stream. */
ZULong ZFileStream_index(const ZFileStream *self) {
    ZAssert(self != NULL, "<self> was NULL!");
    return (self->chunkIndex * ZLANG_CHUNK_SIZE) + self->byteIndex;
}

/** Closes a file stream. */
void ZFileStream_delete(ZFileStream *self) {
    ZAssert(self != NULL, "<self> was NULL!");
    ZAssert(self->file != NULL, "<self>'s FILE handle was NULL!");
    fclose(self->file);
    self->file = NULL;
}
