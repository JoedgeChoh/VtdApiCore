/* ===================================================
 *  file:       Iface.hh
 * ---------------------------------------------------
 *  purpose:	Interface base class
 * ---------------------------------------------------
 *  first edit:	08.01.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  08.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_IFACE_HH
#define _FRAMEWORK_IFACE_HH

// ====== INCLUSIONS ======
#include <string>

namespace Framework
{

class Iface
{
    public:
        /**
        * constructor
        *   @param  name name under which data is managed
        */
        explicit Iface( const std::string & name );

        /**
        * Destroy the class. 
        */
        virtual ~Iface();
        
    protected:
        /**
        * name of the interface
        */
        std::string mName;
        
    public:
        /**
        * get the name of the interface
        * @return the interface's name
        */
        const std::string & getName() const;
};
} // namespace Framework

#endif /* _FRAMEWORK_IFACE_HH */
