#ifndef _POINTERUTIL_H
#define _POINTERUTIL_H

#include <typeinfo>

namespace VTD {
namespace Util {

    /**
     * Avoids dynamic_cast when casting to same type.
     * Usage: `A* a = DynamicCast<A>(b);`
     **/
    template<typename T1, typename T2> T1* DynamicCast(T2* t) {
        //[GK] TODO: Improve usage to use internal dynamic_cast syntax (T* instead of T).

        return (typeid(T1) == typeid(T2)) ? static_cast<T1*>(t) : dynamic_cast<T1*>(t);
    }

    //[GK] TODO: add pointer to int casts etc.

} //namespace Util
} //namespace VTD

#endif // _POINTERUTIL_H
