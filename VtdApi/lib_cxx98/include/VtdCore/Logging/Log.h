#ifndef _VTDFRAMEWORK_LOG_H
#define _VTDFRAMEWORK_LOG_H

#include <iostream>
#include <cstring>
#include <cerrno>

//TODO: common logging

#if defined(_MSC_VER) && !defined(__PRETTY_FUNCTION__)
#define __PRETTY_FUNCTION__ __FUNCSIG__ 
#endif

#define VTD_LOG(str) std::clog << __PRETTY_FUNCTION__ << ": " << str << std::endl;
#define VTD_LOG_ERR(str) std::cerr << __PRETTY_FUNCTION__ << ": " << str << std::endl;
#define VTD_LOG_WARN(str) VTD_LOG_ERR(str)
#define VTD_LOG_ERRNO(str) std::cerr << __PRETTY_FUNCTION__ << ": " << str << " " << strerror(errno) << std::endl;

#ifdef VTD_DEBUG
    #define VTD_DEBUG_LOG(str) VTD_LOG(str)
    #define VTD_DEBUG_LOG_WARN(str) VTD_LOG_WARN(str)
    #define VTD_DEBUG_LOG_ERR(str) VTD_LOG_ERR(str)
    #define VTD_DEBUG_LOG_ERRNO(str) VTD_LOG_ERRNO(str)
#else
    #define VTD_DEBUG_LOG(str)
    #define VTD_DEBUG_LOG_WARN(str)
    #define VTD_DEBUG_LOG_ERR(str)
    #define VTD_DEBUG_LOG_ERRNO(str)
#endif

#endif //_VTDFRAMEWORK_LOG_H
