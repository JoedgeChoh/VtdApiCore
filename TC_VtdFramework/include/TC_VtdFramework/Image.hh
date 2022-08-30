/* ===================================================
 *  file:       Image.hh
 * ---------------------------------------------------
 *  purpose:	manages a single Image
 * ---------------------------------------------------
 *  first edit:	11.03.2008 by M. Dupuis @ VIRES GmbH
 * ===================================================
 */
#ifndef _VTD_IMAGE_HH
#define _VTD_IMAGE_HH

#include <string>
#include <math.h>
#include <VtdToolkit/viRDBIcd.h>

// ====== INCLUSIONS ======

namespace Framework
{
    
// forward declarations
class Image
{
    public:
        /**
        * the image's parameters
        */
        unsigned int   mWidth;
        unsigned int   mHeight;
        unsigned short mPixelSize;
        unsigned short mPixelFormat;
        unsigned long  mDataSize;
        unsigned long  mMaxDataSize;
        unsigned char* mData;
        unsigned int   mId;         
        
    private:
        /**
        * internal image parameters
        */
        unsigned int mFrameNo;
        double       mFrameTime;
        bool         mLastInSeries;
        
        std::string  mName;
        
        /**
        * show verbose output
        */
        bool mVerbose;
        
        /**
        * minimum and maximum output values
        */
        unsigned int mOutValMin;
        unsigned int mOutValMax;
                
    public:
        /**
        * default constructor
        */
        explicit Image( const std::string & name = "myImage" );
        
        /**
        * somewhat copy constructor
        * @param srcImg pointer to source image from which to copy the data
        */
        explicit Image( Image* srcImg );
        
        /**
        * constructor
        * @param width          width of the image [pixel]
        * @param height         height of the image [pixel]
        * @param pixelSize      pixel storage size [bit]
        * @param pixelFormat    storage format of a pixel
        * @param dataSize       size of the image data
        * @param data           the actual image data
        */
        explicit Image( unsigned int width, unsigned int height, unsigned short pixelSize, unsigned short pixelFormat, unsigned long dataSize, void* data );

        /** 
        * Destroy the class.
        */
        virtual ~Image();
        
        /**
        * overload operator for assignment
        * @param rhs    coord for assignment
        */
        void operator= ( const Image& rhs );
        
        /**
        * set the frame number of the image
        * @param no number of the frame in which image was generated
        */
        void setFrameNo( const unsigned int & no );
        
        /**
        * get the frame of the image 
        * @return internal frame number of image
        */
        const unsigned int & getFrameNo() const;
        
        /**
        * set the frame time of the image
        * @param fTime time of the frame in which image was generated
        */
        void setFrameTime( const double & fTime );
        
        /**
        * remember whether image is the last in a row of images
        * @param last   true if image is last in a row of images
        */
        void setLast( bool last = true );
        
        /**
        * tell if image is the last in a row of images
        * @return true if image is last in a row of images
        */
        bool isLast() const;
        
        /**
        * get the frame time of the image 
        * @return internal frame time number of image
        */
        const double & getFrameTime() const;
        
        /**
        * set the id of the image
        * @param no unique of the image
        */
        void setId( const unsigned int & no );
        
        /**
        * get the id of the image 
        * @return internal id of image
        */
        const unsigned int & getId() const;
        
        /**
        * set the name of the image
        * @param name new name of the image
        */
        void setName( const std::string & name );
        
        /**
        * get the name of the image
        * @return name of the image
        */
        const std::string & getName() const;
        
        /**
        * set the image data from RDB
        * @param rdbImg pointer to image read from RDB
        * @return true if successful
        */
        bool setFromRDB( RDB_IMAGE_t* rdbImg );

        /**
        * save the image to a file
        * @param filename name under which to save the image data
        * @return true if successful
        */
        bool saveToFile( const std::string & filename );

        /**
        * save the image to an hdr file
        * @param filename name under which to save the image data
        * @return true if successful
        */
        bool saveToHDRFile( const std::string & filename );
        
        /**
        * convert image to storable format if appropriate
        * @param targetFormat identifier of the target format (0 for auto selection)
        * @return true if successful
        */
        bool convert( unsigned int targetFormat = 0 );
        
        /**
        * set the output range for the format conversion
        * @param minVal minimum output value
        * @param maxVal maximum output value
        */
        void setOutputRange( unsigned int & minVal, unsigned int & maxVal );
        
        /**
        * set the verbose mode
        * @param enable true in order to show some debug info
        */
        void setVerbose( bool enable = true );
        
        /**
        * flip the image vertically
        */
        void flipVert();
        
        /**
        * read an image from a PNG file
        * @param filename name of the file that shall be read
        * @return true if file was read
        */
        bool readPNG( const std::string & filename );
        
        /**
        * print some debug information
        */
        void print();
        
    private:
        /**
        * help methods for saving an RGB image
        */
        size_t putbyte( FILE *outf, unsigned char val );
        size_t putshort( FILE *outf, unsigned short val );
        size_t putlong( FILE *outf, unsigned long val );
        bool putImgName( FILE *outf, const char* name );
        
        /**
        * help methods for saving an RGBE image
        */
        typedef struct {
          int valid;            /* indicate which fields are valid */
          char programtype[16]; /* listed at beginning of file to identify it 
                                 * after "#?".  defaults to "RGBE" */ 
          float gamma;          /* image has already been gamma corrected with 
                                 * given gamma.  defaults to 1.0 (no correction) */
          float exposure;       /* a value of 1.0 in an image corresponds to
                     * <exposure> watts/steradian/m^2. 
                     * defaults to 1.0 */
        } rgbe_header_info;

        /* flags indicating which fields in an rgbe_header_info are valid */
        #define RGBE_VALID_PROGRAMTYPE 0x01
        #define RGBE_VALID_GAMMA       0x02
        #define RGBE_VALID_EXPOSURE    0x04
        
        /* return codes for rgbe routines */
        #define RGBE_RETURN_SUCCESS 0
        #define RGBE_RETURN_FAILURE -1
        
        /* read or write headers */
        /* you may set rgbe_header_info to null if you want to */
        int RGBE_WriteHeader(FILE *fp, int width, int height, rgbe_header_info *info);
        int RGBE_ReadHeader(FILE *fp, int *width, int *height, rgbe_header_info *info);
        
        /* read or write pixels */
        /* can read or write pixels in chunks of any size including single pixels*/
        int RGBE_WritePixels(FILE *fp, float *data, int numpixels);
        int RGBE_ReadPixels(FILE *fp, float *data, int numpixels);
        
        /* read or write run length encoded files */
        /* must be called to read or write whole scanlines */
        int RGBE_WritePixels_RLE(FILE *fp, float *data, int scanline_width,
                     int num_scanlines);
        int RGBE_ReadPixels_RLE(FILE *fp, float *data, int scanline_width,
                    int num_scanlines);
        
        int rgbe_error(int rgbe_error_code, const char *msg);
        
        void float2rgbe(unsigned char rgbe[4], float red, float green, float blue);
        
        void rgbe2float(float *red, float *green, float *blue, unsigned char rgbe[4]);
        
        int RGBE_WriteBytes_RLE(FILE *fp, unsigned char *data, int numbytes);

};

} // namespace Framework

#endif /* _VTD_IMAGE_HH */
