/* ===================================================
 *  file:       Camera.hh
 * ---------------------------------------------------
 *  purpose:	manages a single Camera
 * ---------------------------------------------------
 *  first edit:	19.10.2007 by M. Dupuis @ VIRES GmbH
 *  last mod.:  19.10.2007 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _FRAMEWORK_CAMERA_HH
#define _FRAMEWORK_CAMERA_HH

// ====== INCLUSIONS ======
#include "CoordFr.hh"

namespace Framework
{
    
// forward declaration
class Camera
{
    public:
        /**
        * constructor
        */
        explicit Camera();

        /** 
        * Destroy the class.
        */
        virtual ~Camera();
        
        /**
        * print some information
        */
        void print();
         
        /**
        * set the co-ordinate of the eyepoint
        * @param pos inertial position and orientation of the eyepoint
        */
        void setPos( const CoordFr & pos );
         
        /**
        * get the current co-ordinate of the eyepoint
        * @return current inertial position and orientation of the eyepoint
        */
        const CoordFr & getPos();
        
        /**
        * set the ID
        * @param id new ID
        */
        void setId( unsigned int id );
        
        /**
        * get the ID
        * @return camera ID
        */
        unsigned int getId();
        
        /**
        * get the width
        * @return width in [pixel]
        */
        int getWidth() const;
        
        /**
        * get the height
        * @return height in [pixel]
        */
        int getHeight() const;
        
        /**
        * set the intrinsic parameters
        * @param width      width of viewport                                      [pixel]
        * @param height     height of viewport                                     [pixel]
        * @param near       near clipping plane                                        [m]
        * @param far        far clipping plane                                         [m]
        * @param focalX     focal length in x direction                            [pixel]
        * @param focalY     focal length in y direction                            [pixel]
        * @param principalX position of principal point in x direction             [pixel]
        * @param principalY position of principal point in y direction             [pixel]
        */
        void setIntrinsicParams( const int & width, const int & height, const float & near, const float & far,
                                 const float & focalX, const float & focalY, const float & principalX, const float & principalY );
        
        /**
        * retrieve the intrinsic parameters
        * @param width      width of viewport                                      [pixel]
        * @param height     height of viewport                                     [pixel]
        * @param near       near clipping plane                                        [m]
        * @param far        far clipping plane                                         [m]
        * @param focalX     focal length in x direction                            [pixel]
        * @param focalY     focal length in y direction                            [pixel]
        * @param principalX position of principal point in x direction             [pixel]
        * @param principalY position of principal point in y direction             [pixel]
        */
        void getIntrinsicParams( int & width, int & height, float & near, float & far,
                                 float & focalX, float & focalY, float & principalX, float & principalY );
                                 
        /**
        * get the validity of the intrinsic parameters
        * @return true if intrinsic parameters are valid
        */
        bool intrinsicParamsValid() const;
        
        /**
        * convert an inertial co-ordinate into a screen co-ordinate for the current camera
        * @param x  x value of world co-ordinate
        * @param y  y value of world co-ordinate
        * @param z  z value of world co-ordinate
        * @param scrnX  resulting x co-ordinate [pixel]
        * @param scrnY  resulting y co-ordinate [pixel]
        * @param computeMatrix  true in order to compute the matrices (upon change of camera pos)
        * @return true upon success
        */
        bool inertialToScreen( const double & x, const double & y, const double & z, float &scrnX, float &scrnY, bool computeMatrix = true );

    private:
        /**
        * multiply two 4x4 OpenGL matrices
        * @param result resulting matrix
        * @param matrix1 first matrix
        * @param matrix2 second matrix
        */
        void MultiplyMatrices4by4OpenGL_DOUBLE( double *result, double *matrix1, double *matrix2 );
        
        /**
        * compute window co-ordinates from inertial co-ordinates and according matrices
        * @param objx   inertial object x co-ordinate 
        * @param objy   inertial object y co-ordinate 
        * @param objz   inertial object z co-ordinate
        * @param modelview  model view matrix
        * @param projection projection matrix
        * @param viewport   viewport array
        * @param windowCoordinate   resulting Vec3 window co-ordinate
        * @return   1 upon success, otherwise 0
        */
        int igGlProject( const double & objx, const double & objy, const double & objz, double *modelview, double *projection, int *viewport, float *windowCoordinate );
        
    protected:
        /**
        * unique ID of the camera
        */
        unsigned int mId;
        
        /**
        * eyepoint position and orientation
        */
        CoordFr mPos;
        
        /**
        * intrinsic camera parameters 
        */
        int   mWidth;                      /** width of viewport                                      [pixel] */
        int   mHeight;                     /** height of viewport                                     [pixel] */
        float mNear;                       /** near clipping plane                                        [m] */
        float mFar;                        /** far clipping plane                                         [m] */
        float mFocalX;                     /** focal length in x direction                            [pixel] */
        float mFocalY;                     /** focal length in y direction                            [pixel] */
        float mPrincipalX;                 /** position of principal point in x direction             [pixel] */
        float mPrincipalY;                 /** position of principal point in y direction             [pixel] */
                
        /**
        * are the intrinsic parameters valid?
        */
        bool mIntrinsicParamsValid;
                
 };
} // namespace Smart

#endif /* _CAMERA_HH */
