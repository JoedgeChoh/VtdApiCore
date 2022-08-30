/* ===================================================
 *  file:       Intersection.hh
 * ---------------------------------------------------
 *  purpose:	class for intersection calculation
 * ---------------------------------------------------
 *  first edit:	02.07.2013 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_INTERSECTION_HH
#define _FRAMEWORK_INTERSECTION_HH

/* ====== INCLUSIONS ====== */
#include <math.h>

namespace Framework 
{
    
class Intersection 
{
    public:
        // A floating point number
        //
        typedef double SCALAR;
        
        //
        // A 3D vector
        //
        class VECTOR
        {
            public:
                SCALAR x,y,z; //x,y,z coordinates
        
            public:
        
                VECTOR(): x(0), y(0), z(0)
                {}
        
                VECTOR( const SCALAR& a, const SCALAR& b, const SCALAR& c ) : x(a), y(b), z(c)
                {}
                //index a component
                
                //NOTE: returning a reference allows
                
                //you to assign the indexed element
                
                SCALAR& operator [] ( const long i )
                {
                    return *((&x) + i);
                }
                
                //compare
                
                bool operator == ( const VECTOR& v ) const
                {
                    return (v.x==x && v.y==y && v.z==z);
                }
                
                bool operator != ( const VECTOR& v ) const
                {
                    return !(v == *this);
                }
                
                //negate
                const VECTOR operator - () const
                {
                    return VECTOR( -x, -y, -z );
                }
                
                //assign
                const VECTOR& operator = ( const VECTOR& v )
                {
                    x = v.x;
                    y = v.y;
                    z = v.z;
                    
                    return *this;
                }
                
                //increment
                const VECTOR& operator += ( const VECTOR& v )
                {
                    x+=v.x;
                    y+=v.y;
                    z+=v.z;
                    
                    return *this;
                }
                
                //decrement
                const VECTOR& operator -= ( const VECTOR& v )
                {
                    x-=v.x;
                    y-=v.y;
                    z-=v.z;
                    
                    return *this;
                }
                
                //self-multiply
                const VECTOR& operator *= ( const SCALAR& s )
                {
                    x*=s;
                    y*=s;
                    z*=s;
                    
                    return *this;
                }
                
                //self-divide
                const VECTOR& operator /= ( const SCALAR& s )
                {
                    const SCALAR r = 1 / s;
        
                    x *= r;
                    y *= r;
                    z *= r;
                    
                    return *this;
                }
                
                //add
                const VECTOR operator + ( const VECTOR& v ) const
                {
                    return VECTOR(x + v.x, y + v.y, z + v.z);
                }
                
                //subtract
                const VECTOR operator - ( const VECTOR& v ) const
                {
                    return VECTOR(x - v.x, y - v.y, z - v.z);
                }
                
                //post-multiply by a scalar
                const VECTOR operator * ( const SCALAR& s ) const
                {
                    return VECTOR( x*s, y*s, z*s );
                }
                
                //pre-multiply by a scalar
                friend inline const VECTOR operator * ( const SCALAR& s, const VECTOR& v )
                {
                    return v * s;
                }
                
                //divide
                const VECTOR operator / (SCALAR s) const
                {
                    s = 1/s;
                    return VECTOR( s*x, s*y, s*z );
                }
                
                //cross product
                
                const VECTOR cross( const VECTOR& v ) const
                {
                    //Davis, Snider, "Introduction to Vector Analysis", p. 44
                    return VECTOR( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
                }
                
                //scalar dot product
                SCALAR dot( const VECTOR& v ) const
                {
                    return x*v.x + y*v.y + z*v.z;
                }
                
                //length
                SCALAR length() const
                {
                    return (SCALAR)sqrt( (double)this->dot(*this) );
                }
                
                //unit vector
                const VECTOR unit() const
                {
                    return (*this) / length();
                }
                
                //make this a unit vector
                void normalize()
                {
                    (*this) /= length();
                }
                
                //equal within an error ‘e’
                bool nearlyEquals( const VECTOR& v, const SCALAR e ) const
                {
                    return fabs(x-v.x) < e;
                }
        };
        
        //
        // A 3D position
        //
        typedef VECTOR POINT;     
    
    public:
        /**
        * constructor
        */
        explicit Intersection();

        /**
        * Destroy the class. 
        */
        virtual ~Intersection();
        
        /**
        * calculation of overlapping bounding boxes
        * @param a  extents of object A
        * @param Pa position of object A
        * @param A  orthonormal basis of object A
        * @param b  extents of object B
        * @param Pb position of object B
        * @param B  orthonormal basis of object B
        */
        static bool OBBOverlap ( VECTOR& a, VECTOR& Pa, VECTOR* A,
                                 VECTOR& b, VECTOR& Pb, VECTOR* B ); 
        
};

} // namespace Framework
#endif /* _FRAMEWORK_INTERSECTION_HH */
