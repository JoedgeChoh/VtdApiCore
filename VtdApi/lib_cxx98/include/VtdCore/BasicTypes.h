#ifndef VTDFRAMEWORK_VTDTYPES_H
#define VTDFRAMEWORK_VTDTYPES_H

#include <cstddef>

namespace VTD {

    typedef float Float;
    typedef double Double;

    typedef char Int8;
    typedef short Int16;
    typedef int Int32;
    typedef Int32 Int;

    typedef unsigned char UInt8;
    typedef unsigned short UInt16;
    typedef unsigned int UInt32;
    typedef UInt32 UInt;

#define VTD_INT64_AVAILABLE
#ifdef VTD_OS_LINUX
    typedef long Int64;
    typedef unsigned long UInt64;
#elif VTD_OS_WINDOWS && __cplusplus >= 201103L
    typedef long long Int64;
    typedef unsigned long long UInt64;
#else
    #undef VTD_INT64_AVAILABLE
    typedef Int32 Int64;
    typedef UInt32 UInt64;
#endif

    typedef struct {
        Int64 seconds;
        Int64 microSeconds;
    } TimeValue;

    typedef std::size_t SizeType;
    typedef std::ptrdiff_t PtrDiffType;
}

#endif //VTDFRAMEWORK_VTDTYPES_H
