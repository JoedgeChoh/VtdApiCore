/* ===================================================
 *  file:       BaseClass.hh
 * ---------------------------------------------------
 *  purpose:	basic module functions for all
 *              modules
 * ---------------------------------------------------
 *  first edit:	09.02.2006 by M. Dupuis @ VIRES GmbH
 *  last mod.:  09.01.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_BASECLASS_HH
#define _FRAMEWORK_BASECLASS_HH

// ====== INCLUSIONS ======
#include "ErrorBase.hh"

namespace Framework
{
    
class BaseClass
{
    protected:
        /**
        * the name of this module
        */
        std::string mName;
	
        /**
        * the error handling object (may be inherited from instantiating object)
        */
        Util::ErrorBase *mError;
        
        /**
        * remember whether error handling object has been created locally
        */
        bool mLocalError;
        
    public:
        /**
        * constructor
        *  @param  name    name under which data is managed
        *  @param myError error handling object
        */
        explicit BaseClass( const std::string & name, Util::ErrorBase *myError = NULL );

        /** 
        * Destroy the class
        */
        virtual ~BaseClass();
        
        /**
        * get the name of this entity
        * @return entity's name
        */
        const std::string & getName() const;
        
        /**
        * set the name of this entity
        * @param name   new name
        */
        void setName( const std::string & name );
};
} // namespace Framework

#endif /* _FRAMEWORK_BASECLASS_HH */
