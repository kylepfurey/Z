// .c
// Z Runtime Entry Point
// by Kyle Furey

#include <ZLang.h>

/** Executes a Z program with arguments. */
int main(int argc, char *argv[]) {
    if (argc == 0) {
        ZError("No file was given!");
        return ZLANG_ERROR;
    }
    return Zexecute(argv[argc - 1], (ZArgs){argc - 1, (ZString *) argv + 1});
}
