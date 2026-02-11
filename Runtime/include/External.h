// .h
// Z External Library Includes
// by Kyle Furey

#ifndef ZLANG_EXTERNAL_H
#define ZLANG_EXTERNAL_H

// MACROS
#include <Export.h>

// C STANDARD LIBRARY
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// EXTERNAL LIBRARIES
#ifdef ZLANG_WINDOWS
#include <windows.h>
#endif

#ifdef ZLANG_POSIX
#include <dlfcn.h>
#endif

#include <ffi.h>

#endif // ZLANG_EXTERNAL_H
