/* ===================================================
 *  file:       CoordTrans.hh
 * ---------------------------------------------------
 *  purpose:	class for co-ordinate transformations
 * ---------------------------------------------------
 *  first edit:	21.05.2008 by M. Dupuis @ VIRES GmbH
 *  last mod.:  21.05.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_COORD_TRANS_HH
#define _FRAMEWORK_COORD_TRANS_HH

/* ====== INCLUSIONS ====== */

namespace Framework 
{
    
class CoordTrans 
{
    public:
        /**
        * constructor
        */
        explicit CoordTrans();

        /**
        * Destroy the class. 
        */
        virtual ~CoordTrans();
        
        /**
        * convert a local co-ordinate into an inertial co-ordinate
        * @param    x        local x co-ordinate
        * @param    y        local y co-ordinate
        * @param    z        local z co-ordinate
        * @param    origInX  inertial x position of local co-ordinate system's origin
        * @param    origInY  inertial y position of local co-ordinate system's origin
        * @param    origInZ  inertial z position of local co-ordinate system's origin
        * @param    origInH  orientation of local co-ordinate system around inertial z-axis (Euler angle)
        * @param    origInP  orientation of local co-ordinate system around inertial y-axis (Euler angle)
        * @param    origInR  orientation of local co-ordinate system around inertial x-axis (Euler angle)
        * @param    xIn      resulting inertial x co-ordinate
        * @param    yIn      resulting inertial y co-ordinate
        * @param    zIn      resulting inertial z co-ordinate
        */
        static void local2inertial( const double & x,       const double & y,       const double & z, 
                                    const double & origInX, const double & origInY, const double & origInZ, 
                                    const double & origInH, const double & origInP, const double & origInR, 
                                    double & xIn, double & yIn, double & zIn );
        
        /**
        * convert an inertial co-ordinate into a local co-ordinate
        * @param    x        inertial x co-ordinate
        * @param    y        inertial y co-ordinate
        * @param    z        inertial z co-ordinate
        * @param    origInX  inertial x position of local co-ordinate system's origin
        * @param    origInY  inertial y position of local co-ordinate system's origin
        * @param    origInZ  inertial z position of local co-ordinate system's origin
        * @param    origInH  orientation of local co-ordinate system around inertial z-axis (Euler angle)
        * @param    origInP  orientation of local co-ordinate system around inertial y-axis (Euler angle)
        * @param    origInR  orientation of local co-ordinate system around inertial x-axis (Euler angle)
        * @param    xLoc     resulting local x co-ordinate
        * @param    yLoc     resulting local y co-ordinate
        * @param    zLoc     resulting local z co-ordinate
        */
        static void inertial2local( const double & x,       const double & y,       const double & z, 
                                    const double & origInX, const double & origInY, const double & origInZ, 
                                    const double & origInH, const double & origInP, const double & origInR, 
                                    double & xLoc, double & yLoc, double & zLoc );
        
        /**
        * convert an inertial co-ordinate into a USK co-ordinate
        * @param    x           inertial x co-ordinate
        * @param    y           inertial y co-ordinate
        * @param    z           inertial z co-ordinate
        * @param    uskOrigInX  inertial x position of USK co-ordinate system's origin
        * @param    uskOrigInY  inertial y position of USK co-ordinate system's origin
        * @param    uskOrigInZ  inertial z position of USK co-ordinate system's origin
        * @param    uskOrigInH  orientation of USK's co-ordinate system around inertial z-axis (Euler angle)
        * @param    uskOrigInP  orientation of USK's co-ordinate system around inertial y-axis (Euler angle)
        * @param    uskOrigInR  orientation of USK's co-ordinate system around inertial x-axis (Euler angle)
        * @param    xUSK        resulting USK x co-ordinate
        * @param    yUSK        resulting USK y co-ordinate
        * @param    zUSK        resulting USK z co-ordinate
        */
        static void inertial2usk( const double & x,          const double & y,          const double & z, 
                                  const double & uskOrigInX, const double & uskOrigInY, const double & uskOrigInZ, 
                                  const double & uskOrigInH, const double & uskOrigInP, const double & uskOrigInR, 
                                  double & xUSK, double & yUSK, double & zUSK );

        /**
        * extended version of inertial2usk function to convert an inertial co-ordinate into full calculated USK co-ordinate
        * @param    x           inertial x co-ordinate
        * @param    y           inertial y co-ordinate
        * @param    z           inertial z co-ordinate
        * @param    uskOrigInX  inertial x position of USK co-ordinate system's origin
        * @param    uskOrigInY  inertial y position of USK co-ordinate system's origin
        * @param    uskOrigInZ  inertial z position of USK co-ordinate system's origin
        * @param    uskOrigInH  orientation of USK's co-ordinate system around inertial z-axis (Euler angle)
        * @param    uskOrigInP  orientation of USK's co-ordinate system around inertial y-axis (Euler angle)
        * @param    uskOrigInR  orientation of USK's co-ordinate system around inertial x-axis (Euler angle)
        * @param    xUSK        resulting USK x co-ordinate
        * @param    yUSK        resulting USK y co-ordinate
        * @param    zUSK        resulting USK z co-ordinate
        */
        static void inertial2uskExtended( const double & x,          const double & y,          const double & z,
                                          const double & uskOrigInX, const double & uskOrigInY, const double & uskOrigInZ,
                                          const double & uskOrigInH, const double & uskOrigInP, const double & uskOrigInR,
                                          double & xUSK, double & yUSK, double & zUSK );

        /**
        * convert an inertial orientation into a USK orientation
        * @param    x           inertial heading angle
        * @param    y           inertial pitch angle
        * @param    z           inertial roll angle
        * @param    uskOrigInH  orientation of USK's co-ordinate system around inertial z-axis (Euler angle)
        * @param    uskOrigInP  orientation of USK's co-ordinate system around inertial y-axis (Euler angle)
        * @param    uskOrigInR  orientation of USK's co-ordinate system around inertial x-axis (Euler angle)
        * @param    hUSK        resulting angle around USK z-axis
        * @param    pUSK        resulting angle around USK y-axis
        * @param    rUSK        resulting angle around USK x-axis
        */
        static void inertial2uskHPR( const double & h,          const double & p,          const double & r, 
                                     const double & uskOrigInH, const double & uskOrigInP, const double & uskOrigInR, 
                                     double & hUSK, double & pUSK, double & rUSK );
                                  
        /**
        * convert a given (inertial) orientation into the orientation in a rotated co-ordinate system
        * @param    x           inertial heading angle
        * @param    y           inertial pitch angle
        * @param    z           inertial roll angle
        * @param    sysInH     orientation of rotated system's co-ordinate system around inertial z-axis (Euler angle)
        * @param    sysInP     orientation of rotated system's co-ordinate system around inertial y-axis (Euler angle)
        * @param    sysInR     orientation of rotated system's co-ordinate system around inertial x-axis (Euler angle)
        * @param    hRes        resulting angle around rotated system's z-axis
        * @param    pRes        resulting angle around rotated system's y-axis
        * @param    rRes        resulting angle around rotated system's x-axis
        */
        static void transformHPR( const double & h,      const double & p,      const double & r, 
                                  const double & sysInH, const double & sysInP, const double & sysInR, 
                                  double & hRes, double & pRes, double & rRes );
                                  
        /**
        * normalize an angle between 0 and 2 pi 
        * @param  angle incoming angle
        * @param  resulting normalized angle
        */
        static double normalizeAngleRad( const double & angle );
        
        /**
        * calculate cross product of two Vec3 arrays
        * @param result pointer to the resulting vector
        * @param a  first vector
        * @param b  second vector
        */
        static void crossVec3( double* result, double* a, double* b );
        
        /**
        * normalize a Vec3
        * @param a  vector which is to be normalized
        */
        static void normVec3( double* a );
        
        /**
        * get the inverse of a square matrix
        * @param  tgt space for target matrix (allocated by user)
        * @param  src pointer to source matrix
        * @param  noElem number of elements in the matrix
        * @return true if inverse could be computed
        */
        static bool matrixGetInverse( double* tgt, double *src, unsigned int noElem ); 
        
        /**
        * get the determinant of a square matrix
        * @param  src pointer to source matrix
        * @param  noElem number of elements in the matrix
        * @return determinant value
        */
        static double matrixGetDeterminant( double *src, unsigned int noElem ); 
        
        /**
        * multiply a 3-component vector by a 3x3 matrix
        * @param a  first vector component
        * @param b  second vector component
        * @param c  third vector component
        * @param mat pointer to first matrix element
        * @param aRes first element of resulting vector
        * @param bRes second element of resulting vector
        * @param cRes third element of resulting vector
        */
        static void transformVec3( const double & a, const double & b, const double & c, double* mat, 
                                   double & aRes, double & bRes, double & cRes );

        /**
        * get the Euler matrix from given heading, pitch and roll angles
        * @param mat pointer to first matrix element (must be allocated by user to hold 9 double values)
        * @param h heading angle
        * @param p pitch angle
        * @param r roll angle
        */
        static bool getEulerMat3( double* mat, const double & h, const double & p, const double & r );
};

} // namespace Framework
#endif /* _FRAMEWORK_COORD_TRANS_HH */
