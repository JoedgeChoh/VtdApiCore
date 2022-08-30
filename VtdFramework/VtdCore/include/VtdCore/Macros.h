#ifndef VTDFRAMEWORK_VI_MACROS_H
#define VTDFRAMEWORK_VI_MACROS_H

//define deprecation macros based on version number that give compiler warnings
//later when files are removed - remove deprecation macros pertaining to
//unsupported version. Build errors show all locations where deprecated
//functionality can be removed.

#define DO_PRAGMA(x) _Pragma (#x)
#define VTD_COMPILETIME_WARNING(x) DO_PRAGMA(GCC warning x)
#define VTD_COMPILETIME_ERROR(x) DO_PRAGMA(GCC error x)

#define VTD_DEPRECATED_FILE(msg) VTD_COMPILETIME_WARNING("Deprecated: " msg)
#ifdef __GNUC__
    #if __GNUC__ >= 4 && __GNUC_MINOR__ >= 8
        #define VTD_DEPRECATED(msg, var) var __attribute__ ((deprecated(msg)))
        #define VTD_DEPRECATED_FUNC(msg, func) VTD_DEPRECATED(msg, func)
    #else
        #define VTD_DEPRECATED(msg, var) var __attribute__ ((deprecated))
        #define VTD_DEPRECATED_FUNC(msg, func) VTD_DEPRECATED(msg, func)
    #endif
#elif defined(_MSC_VER)
    #define VTD_DEPRECATED(msg, var) __declspec(deprecated) var
    #define VTD_DEPRECATED_FUNC(msg, func) VTD_DEPRECATED(msg, func)
#else
    VTD_COMPILETIME_WARNING("Deprecated not implemented for this compiler")
    #define VTD_DEPRECATED(msg, var) var
    #define VTD_DEPRECATED_FUNC(msg, func) func
#endif

#define VTD_DEPRECATED_2_1_1(msg, var) VTD_DEPRECATED(msg, var)
#define VTD_DEPRECATED_2_1_1_FUNC(msg, func) VTD_DEPRECATED_FUNC(msg, func)
#define VTD_DEPRECATED_2_1_1_FILE(msg) VTD_DEPRECATED_FILE(msg)

#define VTD_DEPRECATED_2020_0(msg, var) VTD_DEPRECATED(msg, var)
#define VTD_DEPRECATED_2020_0_FUNC(msg, func) VTD_DEPRECATED_FUNC(msg, func)
#define VTD_DEPRECATED_2020_0_FILE(msg) VTD_DEPRECATED_FILE(msg)

#define VTD_NOT_IMPLEMENTED(msg) VTD_COMPILETIME_WARNING("Not Implemented: " msg)

#define VTD_UNUSED(_var) static_cast<void>(_var)

#include <assert.h>
    #define VTD_ASSERT(x) assert(x)
#ifdef VTD_DEBUG
    #define VTD_DEBUG_ASSERT(x) VTD_ASSERT(x)
#else
    #define VTD_DEBUG_ASSERT(x)
#endif



#if __cplusplus >= 201103L
    #define VTD_OVERRIDE override
    #define VTD_FINAL final

    /**
     * Compile time assertion, msg should be given as a string literal, see documentation of static_assert.
     */
    #define VTD_COMPILETIME_ASSERT(exp, msg) static_assert(exp, #msg)
#else
    //not supported, define as empty
    #define VTD_OVERRIDE
    #define VTD_FINAL

    //no static-assert available before c++11, so we need to define our own
    template<bool> struct CompileTimeAssert;
    template<> struct CompileTimeAssert<true> {};

    /**
     * Compile time assertion, msg should be given as a string literal so code will compile with c++11 compilers. (See static_assert)
     */
    #define VTD_COMPILETIME_ASSERT(exp, msg) (CompileTimeAssert<(exp)!=0>())
#endif


#ifdef __GNUC__

    /** not quite c++11 noexcept and not c++98 throw() either.
     * In some situations the standard library will only use
     * existing functions if they are known to be non throwing.
     */
    #define VTD_NOTHROW __attribute__((nothrow))
#else
    #define VTD_NOTHROW
#endif

#endif //VTDFRAMEWORK_VI_MACROS_H
