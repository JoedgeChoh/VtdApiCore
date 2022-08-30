#ifndef _TEST_DEFINITION_H
#define _TEST_DEFINITION_H

#include <map>

namespace  test_definition
{
    
    typedef struct TESTDEFINITION
    {
        bool makePictures;
        std::vector<uint> sharedMemoryKeys;
        unsigned int numOfSharedMemories;
        unsigned int releaseFlag;
        std::string testName;
        bool rdbTrigger;
        double testTime;
        std::string filterParameters;
        bool png;
        bool raw;
        bool bmp;
        bool tga;
        bool jpg;
        bool csv;
        bool hdf5;
        
    }TestDefinition_t;
    
    typedef struct VtdTest
    {
        std::vector<TestDefinition_t> tests;
        std::multimap<int, std::string> setups;
        std::multimap<int, std::string> projects;
        std::multimap<int, std::string> scenarios;
        std::string vtdRootPath;
        std::string hdf5Path;
        std::string csvPath;
        std::string picturePath;
        std::string logFileName;
        bool verbose;
        bool writeCsv;
        bool writeHdf5;
    }VtdTest;
}
 
#endif // _TEST_DEFINITION_H
