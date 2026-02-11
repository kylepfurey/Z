// .h
// Z Export Macro
// by Kyle Furey

#ifndef ZLANG_EXPORT_H
#define ZLANG_EXPORT_H

/** The current Z runtime version. */
#define ZLANG_VER 1.0

/** Z "home" environment variable. */
#define ZLANG_HOME "Z_HOME"

#if defined(_WIN32) || defined(_WIN64)
/** File path separator. */
#define ZLANG_SEPARATOR '\\'
#ifdef ZLANG_EXPORTS
/** Windows Export */
#define ZLANG_API __declspec(dllexport)
#else
/** Windows Import */
#define ZLANG_API __declspec(dllimport)
#endif
#else
/** File path separator. */
#define ZLANG_SEPARATOR '/'
#ifdef ZLANG_EXPORTS
/** MacOS / Linux Export */
#define ZLANG_API __attribute__((visibility("default")))
#else
/** Fallback */
#define ZLANG_API
#endif
#endif

#ifdef _DEBUG
/** Z Runtime Debugging */
#define ZLANG_DEBUG
#endif

#endif // ZLANG_EXPORT_H
