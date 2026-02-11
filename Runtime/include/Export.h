// .h
// Z Export Macro
// by Kyle Furey

#ifndef ZLANG_EXPORT_H
#define ZLANG_EXPORT_H

/** The current Z runtime version. */
#define ZLANG_VER 1.0

#if defined(_WIN32) || defined(_WIN64)
#ifdef ZLANG_EXPORTS
/** Windows Export */
#define ZLANG_API __declspec(dllexport)
#else
/** Windows Import */
#define ZLANG_API __declspec(dllimport)
#endif
#else
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
