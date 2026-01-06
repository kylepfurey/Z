// .c
// Z File Operation Functions
// by Kyle Furey

#include <ZLang.h>

/** Loads a .zac or .zlib program at the given path into a file stream. */
ZBool ZFileLoad(ZString path, ZFileStream *file_stream) {
    ZAssert(path != NULL, "<path> was NULL!");
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZDiff length = (ZDiff) strlen(path);
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
    file_stream->size = fread(file_stream->chunk, 1, ZLANG_CHUNK_SIZE, file);
    if (file_stream->chunk[0] != ZOPCODE_MAGIC) {
        fclose(file);
        ZError("File does not start with the Z byte!");
        return false;
    }
    if (file_stream->size <= 1) {
        fclose(file);
        ZError(
            file_stream->size == 0 ?
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
    fseek(file, ZLANG_CHUNK_SIZE, SEEK_SET);
    file_stream->index = 1;
    file_stream->chunk_index = 0;
    file_stream->file = file;
    return true;
}

/** Outputs the current byte of a file stream. */
ZBool ZFileCurrent(ZFileStream *file_stream, ZByte *byte) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(file_stream->file != NULL, "<file_stream>'s FILE handle was NULL!");
    ZAssert(byte != NULL, "<byte> was NULL!");
    if (file_stream->index >= file_stream->size) {
        return false;
    }
    *byte = file_stream->chunk[file_stream->index];
    return true;
}

/** Outputs the next byte of a file stream, iterating chunks when needed. */
ZBool ZFileNext(ZFileStream *file_stream, ZByte *byte) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(file_stream->file != NULL, "<file_stream>'s FILE handle was NULL!");
    ZAssert(byte != NULL, "<byte> was NULL!");
    if (file_stream->index >= file_stream->size) {
        return false;
    }
    *byte = file_stream->chunk[file_stream->index++];
    if (file_stream->index == file_stream->size) {
        file_stream->index = 0;
        ++file_stream->chunk_index;
        file_stream->size = fread(file_stream->chunk, 1, ZLANG_CHUNK_SIZE, file_stream->file);
        if (file_stream->size == 0) {
            return false;
        }
    }
    return true;
}

/** Outputs an array of bytes from a file stream, iterating chunks when needed. */
ZBool ZFileNextArray(ZFileStream *file_stream, ZSize size, ZByte *array) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(file_stream->file != NULL, "<file_stream>'s FILE handle was NULL!");
    ZAssert(array != NULL, "<array> was NULL!");
    ZInt endian = 1;
    if (*(ZByte *) &endian == 1) {
        for (; size > 0; --size) {
            if (!ZFileNext(file_stream, array++)) {
                return false;
            }
        }
    } else {
        array += size;
        for (; size > 0; --size) {
            if (!ZFileNext(file_stream, --array)) {
                return false;
            }
        }
    }
    return true;
}

/** Jumps to the given byte index in a file stream. */
ZBool ZFileJump(ZFileStream *file_stream, ZIndex index) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(file_stream->file != NULL, "<file_stream>'s FILE handle was NULL!");
    ZUInt chunk = (index / ZLANG_CHUNK_SIZE) * ZLANG_CHUNK_SIZE;
    if (file_stream->chunk_index != chunk) {
        file_stream->chunk_index = chunk;
        fseek(file_stream->file, chunk, SEEK_SET);
        file_stream->size = fread(file_stream->chunk, 1, ZLANG_CHUNK_SIZE, file_stream->file);
    }
    file_stream->index = index % ZLANG_CHUNK_SIZE;
    return file_stream->index < file_stream->size;
}

/** Returns the current byte index of a file stream. */
ZIndex ZFileIndex(const ZFileStream *file_stream) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    return (file_stream->chunk_index * ZLANG_CHUNK_SIZE) + file_stream->index;
}

/** Closes a file stream. */
void ZFileClose(ZFileStream *file_stream) {
    ZAssert(file_stream != NULL, "<file_stream> was NULL!");
    ZAssert(file_stream->file != NULL, "<file_stream>'s FILE handle was NULL!");
    fclose(file_stream->file);
    file_stream->file = NULL;
}
