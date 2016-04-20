// Inclusion of this file is only needed when building
//  engine 
//  engine_graphics
//  artiste
// NOT needed when using these libraries.

#pragma once
// unused macro
#define VSX_UNUSED(arg) (void)arg

// inlining macro
#ifdef VSX_OPTIMIZATIONS
#define VSX_ALWAYS_INLINE __attribute__((always_inline))
#else
#define VSX_ALWAYS_INLINE
#endif


#define PLATFORM_WINDOWS          0
#define PLATFORM_LINUX          1
#define PLATFORM_MACINTOSH      2
#define PLATFORM_WM6                  3
#define PLATFORM_ANDROID          4
#define PLATFORM_SOMETHINGELSE    1000

#define PLATFORM_FAMILY_WINDOWS 0
#define PLATFORM_FAMILY_UNIX 1
#define PLATFORM_FAMILY_OTHER 2

#define COMPILER_GCC 1
#define COMPILER_MINGW 2
#define COMPILER_VISUAL_STUDIO 4


#ifndef PLATFORM
    #if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64)
      #ifdef __GNUC__
        #define COMPILER COMPILER_MINGW + COMPILER_GCC
      #endif
      #ifdef _MSC_VER
        #define COMPILER COMPILER_VISUAL_STUDIO
      #endif
        #define PLATFORM                                        PLATFORM_WINDOWS
        #define PLATFORM_NAME                                   "Windows"
        #define PLATFORM_FAMILY                                 PLATFORM_FAMILY_WINDOWS
        #define PLATFORM_SHARED_FILES                           vsx_string<>("share\\")
        #define PLATFORM_DLL_SUFFIX                             ".dll"
        #ifdef PLATFORM_SHARED_FILES_STL
          #define PLATFORM_SHARED_FILES_STLSTRING               std::string("share\\")
        #endif
        #define DIRECTORY_SEPARATOR                             "\\"
        #define DIRECTORY_SEPARATOR_CHAR                             '\\'

    #elif defined(__APPLE__) || defined(__MACH__)
        #define PLATFORM                                        PLATFORM_MACINTOSH
        #define PLATFORM_NAME                                   "Macintosh"
        #define PLATFORM_FAMILY                                 PLATFORM_FAMILY_UNIX
        #define PLATFORM_SHARED_FILES                           vsx_string<>("")
        #define PLATFORM_DLL_SUFFIX                             ".dylib"
        #ifdef PLATFORM_SHARED_FILES_STL
          #define PLATFORM_SHARED_FILES_STLSTRING                         std::string("")
        #endif
        #define DIRECTORY_SEPARATOR                             "/"
        #define DIRECTORY_SEPARATOR_CHAR                        '/'
    #elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__CYGWIN__)
        #define COMPILER COMPILER_GCC
        #define PLATFORM                                        PLATFORM_LINUX
        #define PLATFORM_NAME                                   "GNU / Linux"
        #define PLATFORM_FAMILY                                 PLATFORM_FAMILY_UNIX
        #define PLATFORM_SHARED_FILES                           vsx_string<>(CMAKE_INSTALL_PREFIX)+vsx_string<>("/share/vsxu/")
        #define PLATFORM_DLL_SUFFIX                             ".so"
        #ifdef PLATFORM_SHARED_FILES_STL
          #define PLATFORM_SHARED_FILES_STLSTRING               std::string(CMAKE_INSTALL_PREFIX)+std::string("/share/vsxu/")
        #endif
        #define DIRECTORY_SEPARATOR                             "/"
        #define DIRECTORY_SEPARATOR_CHAR                        '/'
    #else
        #define PLATFORM                                        PLATFORM_SOMETHINGELSE
        #define PLATFORM_NAME                                   "Something Else"
        #define PLATFORM_FAMILY                                 PLATFORM_FAMILY_OTHER
        #define PLATFORM_SHARED_FILES                           ""
        #define DIRECTORY_SEPARATOR                             "/"
        #define DIRECTORY_SEPARATOR_CHAR                        '/'
    #endif

    /*
        How many bits is this system?
    */

    // Windows
    #if (defined(_WIN64) || defined(WIN64))
        #define PLATFORM_BITS                                   64
    // Macintosh
    #elif (defined(__LP64__) || defined(_LP64) || defined(__ppc64__))
        #define PLATFORM_BITS                                   64
    // Linux
    #elif (defined(__x86_64__) || defined(__64BIT__) || (__WORDSIZE == 64))
        #define PLATFORM_BITS                                   64
    #else
        #define PLATFORM_BITS                                   32
    #endif

    #ifdef vsx_string
      #undef vsx_string
    #endif

#endif

// packing
#if COMPILER == COMPILER_GCC
#define VSX_PACK_BEGIN
#define VSX_PACK_END __attribute__((__packed__));
#endif

#if COMPILER == COMPILER_VISUAL_STUDIO
#define __PRETTY_FUNCTION__ L""
#define VSX_PACK_BEGIN __pragma( pack(push, 1) )
#define VSX_PACK_END ; __pragma( pack(pop) )
#endif


// aligned malloc
#if COMPILER == COMPILER_VISUAL_STUDIO
  #include <malloc.h>
  #define vsx_aligned_malloc(n) _aligned_malloc(n, 64)
  #define vsx_aligned_realloc(pointer, n) _aligned_realloc(pointer, n, 64)
  #define vsx_aligned_free(pointer) _aligned_free(pointer)
#endif


#if PLATFORM_FAMILY == PLATFORM_FAMILY_UNIX
  #define vsx_aligned_malloc(n) aligned_alloc(64, n)
  #define vsx_aligned_realloc(pointer, n) realloc(pointer, n)
  #define vsx_aligned_free(pointer) free(pointer)
#endif

#define WIDE2(x) L ##x
#define WIDE1(x) WIDE2(x)
