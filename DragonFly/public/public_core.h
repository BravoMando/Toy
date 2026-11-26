#ifndef DRAGONFLY_CORE_API_HEADER
#define DRAGONFLY_CORE_API_HEADER

#include <stddef.h>
#include <stdint.h>

#if __cplusplus
  #define BEGIN_EXTERN_C extern "C" {
#else
  #define BEGIN_EXTERN_C
#endif

#if __cplusplus
  #define END_EXTERN_C }
#else
  #define END_EXTERN_C
#endif

#if __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C
#endif

#if __cplusplus
  #define NOEXCEPT noexcept
#else
  #define NOEXCEPT
#endif

#if defined(_MSC_VER) && !defined(__clang__)
  #define COMPILER_MSVC 1
#elif defined(__clang__) && defined(_MSC_VER)
  #define COMPILER_CLANG_CL 1
#elif defined(__clang__)
  #define COMPILER_CLANG 1
#elif defined(__MINGW32__) || defined(__MINGW64__)
  #define COMPILER_MINGW 1
#elif defined(__GNUC__)
  #define COMPILER_GCC 1
#else
  #define COMPILER_UNKNOWN 1
#endif

#if BUILD_SDK
  #if COMPILER_MSVC || COMPILER_CLANG_CL
    #define DRAGONFLY_EXPORT_SYMBOL __declspc(dllexport)
  #else
    #define DRAGONFLY_EXPORT_SYMBOL __attribute__((visibility("default")))
  #endif
#else
  #if COMPILER_MSVC || COMPILER_CLANG_CL
    #define DRAGONFLY_EXPORT_SYMBOL __declspec(dllimport)
  #else
    #define DRAGONFLY_EXPORT_SYMBOL
  #endif
#endif

#define DRAGONFLY_API_CALL

#define OFFSET_OF(TYPE, member) \
  ((ptrdiff_t)(&((TYPE *)0)->member))

#define CONTAINER_OF(TYPE, ptr, member) \
  ((TYPE *)((unsigned char *)(ptr) - OFFSET_OF(TYPE, member)))

#endif

