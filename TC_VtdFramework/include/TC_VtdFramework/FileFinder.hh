
#ifndef FU_FILEFINDER_H
#define FU_FILEFINDER_H

// includes
#include <string>
#include <vector>

namespace Framework {

class FileFinder
{
    public:

        enum FindResult {
            FINDER_NOT_FOUND,
            FINDER_FOUND_PRIMARY,
            FINDER_FOUND_PATH_LIST
        };

        explicit FileFinder( const std::string& arsPathListPrimary,
                             const std::string& arsPathListSecondary,
                             char               acSeparatorChar = ':' );

        explicit FileFinder( bool showDebugInfo = false );

        virtual ~FileFinder();

        FindResult      locateFile                  ( const std::string& arsFilePath,
                                                      std::string&       arsLocation );

        bool            isFileReadable              ( const std::string& arsPath ) const;

        /**
        * initialize the file finder
        */
        void init( const std::string& arsPathListPrimary,
                   const std::string& arsPathListSecondary,
                   char               acSeparatorChar = ':' );

        /**
        * get the file paths from environment variables
        * @return true if environment settings were found
        */
        bool pathsFromEnv();

        /**
        * get the primary path which was retrieved from environment settings
        * @return   primary path as string
        */
        const std::string & getPrimaryPath() const;

        /**
        * get the secondary path which was retrieved from environment settings
        * @return   secondary path as string
        */
        const std::string & getSecondaryPath() const;

    private:

        void            createPathVector            ( const std::string&            arsPathList,
                                                      std::vector< std::string >&   arPathVector );

        void            addPathToVector             ( const std::string&            arsPath,
                                                      std::vector< std::string >&   arPathVector );

        std::string     trim                        ( const std::string&            arsString );

        void            createExtendedFilenames     ( const std::string&            arsFilePath,
                                                      std::vector< std::string >&   rExtendedFilenames );


    private:

        /** typedef for a path vector iterator */
        typedef std::vector< std::string >::const_iterator  PathVectorIt;

        /** char used to separate the paths in the list */
        char                                mcSeparator;

        /** single primary paths after separation */
        std::vector< std::string >          mPathVectorPrimary;

        /** single secondary paths after separation */
        std::vector< std::string >          mPathVectorSecondary;

        /** primary path, retrieved from environment */
        std::string                         mPrimaryPath;

        /** secondary path, retrieved from environment */
        std::string                         mSecondaryPath;

};

} // end of namespace Framework

#endif
