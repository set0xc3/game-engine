#ifndef CORE_BASE_H
#define CORE_BASE_H

// Base Types

#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i8  b8;
typedef i16 b16;
typedef i32 b32;
typedef i64 b64;

#define local_variable  static
#define global_variable static
#define internal        static

#define Bytes(value)     (value)
#define Kilobytes(value) (value << 10)
#define Megabytes(value) (value << 20)
#define Gigabytes(value) ((u64)(value) << 30)
#define Terabytes(value) ((u64)(value) << 40)

#define ArrayCount(a) (sizeof((a)) / sizeof(*(a)))

// Platform Types

#ifdef __linux__
#define PLATFORM_LINUX
#elif __WIN32__
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_LINUX
#define PLATFORM_LIB_EXT "so"
#define PLATFORM_SLASH   '/'
#elif PLATFORM_WINDOWS
#define PLATFORM_LIB_EXT "dll"
#define PLATFORM_SLASH   '\\'
#endif

#ifdef PLATFORM_LINUX
#ifdef BUILD_LIB_SHARED
#define API __attribute__((visibility("default")))
#else
#define API
#endif
#elif PLATFORM_WINDOWS
#ifdef BUILD_LIB_SHARED
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#endif

#endif // CORE_BASE_H
