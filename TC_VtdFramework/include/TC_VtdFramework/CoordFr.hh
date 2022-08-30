/* ===================================================
 *  file:       CoordFr.hh
 * ---------------------------------------------------
 *  purpose:	container for a co-ordinate
 * ---------------------------------------------------
 *  first edit:	07.01.2009 by M. Dupuis @ VIRES GmbH
 *  last mod.:  07.01.2009 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_COORD_HH
#define _FRAMEWORK_COORD_HH

// ====== INCLUSIONS ======

namespace Framework
{

class CoordFr
{
    public:
        /**
        * get distance of two co-ordinates
        * @param coord1 position 1
        * @param coord2 position 2
        * @return inertial distance
        */
        static double getDist( const CoordFr & coord1, const CoordFr & coord2 ); 
        
        /**
        * get 2d distance of two co-ordinates
        * @param coord1 position 1
        * @param coord2 position 2
        * @return inertial distance in xy-plane
        */
        static double getDist2d( const CoordFr & coord1, const CoordFr & coord2 ); 
        
        /**
        * two constants for unit conversion
        */
        static const double Deg2Rad; 
        static const double Rad2Deg; 
    
    private:
        /**
        * co-ordinate values:
        *   x, y, z, heading, pitch, roll
        */
        double  mX;     // [m]
        double  mY;     // [m]
        double  mZ;     // [m]
        double  mH;     // [rad]
        double  mP;     // [rad]
        double  mR;     // [rad]

    public:
        /**
        * primitive constructor
        */
        explicit CoordFr();

        /**
        * constructor
        *   @param  x   x-value
        *   @param  y   y-value
        *   @param  z   z-value
        *   @param  h   heading
        *   @param  p   pitch
        *   @param  r   roll
        */
        explicit CoordFr( const double & x, const double & y, const double & z,
                        const double & h = 0.0, const double & p = 0.0, const double & r = 0.0 );

        /**
        * destructor
        */
        virtual ~CoordFr();
        
        /**
        * overload operator for value assignment
        * @param rhs    coord for assignment
        */
        void operator= ( const CoordFr & rhs );
        
        /**
        * overload operator for scalar multiplication
        * @param rhs    scalar for multiplication
        */
        CoordFr operator* ( const double & rhs );
        
        /**
        * add two co-ordinates
        * @param rhs    second co-ordinate
        */
        CoordFr operator+ ( const CoordFr & rhs );
        
        /**
        * subtract two co-ordinates
        * @param rhs    second co-ordinate
        */
        CoordFr operator- ( const CoordFr & rhs );
        
        /**
        * increase co-ordinate
        * @param rhs    second co-ordinate
        */
        void operator+= ( const CoordFr & rhs );
        
        /**
        * increase co-ordinate
        * @param rhs    second co-ordinate
        */
        void operator-= ( const CoordFr & rhs );
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getX() const;
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getY() const;
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getZ() const;
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getH() const;
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getP() const;
        
        /**
        * member access function
        *   @return component of the co-ordinate
        */
        const double & getR() const;
        
        /**
        * set values of all member variable
        *   @param xyz and hpr values
        */
        void set( const double & x, const double & y, const double & z,
                  const double & h = 0.0, const double & p = 0.0, const double & r = 0.0 );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setX( const double & value );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setY( const double & value );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setZ( const double & value );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setH( const double & value );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setP( const double & value );
        
        /**
        * set value of member variable
        *   @param component of the co-ordinate
        */
        void setR( const double & value );

        /**
        * initialize co-ordinate
        */
        void init();

        /**
        * print a co-ordinaate to stderr
        */
        void print() const;

        /**
        * get the length of the 3d-vector of the first 3 components fo the coordinate
        * @return value of vector (mX, mY, mZ)
        */
        double getValue();

};
} // namespace Framework

#endif /* _FRAMEWORK_COORD_HH */
