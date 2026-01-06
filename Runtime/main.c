// .c
// Z Runtime Entry Point
// by Kyle Furey

#include <ZLang.h>

/** Executes a Z program. */
int main(int argc, char *argv[]) {
    if (argc == 0) {
        ZError("No file was given!");
        return ZLANG_ERROR;
    }
    return ZExecuteFile(argv[argc - 1]);
}
