#ifndef _MODE1_H
#define _MODE1_H

#include <VtdApi/VtdApi.h>
#include <VtdToolkit/Scp/ScpBuilder.h>
#include <VtdCore/Timer.h>
#include <VtdCore/FileSystemIO.h>
#include <VtdCore/XMLConfigReader.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <boost/thread.hpp>

#include "RdbCallback.h"
#include "ImageGenerator.h"


#define MAX_BUFFER_SIZE 256
#define LOG_TEST

// SIMULATION STAGES
enum COMMAND {STOP, START, INIT, LOAD_SCENARIO};

class Mode1
{
public:
    // Vector of scenario list
    typedef std::vector<std::string> ScenarioList;

public:
    /**
     * @brief Mode1 - test model 1 class constructor
     * @param testConfigFileName - test config file name
     */
    Mode1(const std::string& testConfigFileName);

    /**
     * @brief ~Mode1 destructor
     */
    virtual ~Mode1();

    /**
     * @brief runMode1 run whole test model
     */
    void runMode1();

    /**
     * @brief readConfigFile - read config file
     * @return return true if succes
     */
    bool readConfigFile();

private:
    /**
     * @brief RunAndAutoEndScenario - run and end scenario
     * @param testDefinition_t - test parameters
     */
    void RunAndAutoEndScenario(const test_definition::TestDefinition_t& testDefinition_t);

    /**
     * @brief InitScenario - initilazing scenario
     */
    bool InitScenario();

    /**
     * @brief RunScenarioFile - run scenario
     * @param scenarioFileName - scenario file name
     * @param setupFileName - - setup file name
     * @param projectFileName - project file name
     * @param testDefinition_t - test paramters
     */
    void RunScenarioFile(  const std::string& scenarioFileName
                         , const std::string& setupFileName
                         , const std::string& projectFileName
                         , const test_definition::TestDefinition_t& testDefinition_t);

    /**
     * @brief startVtd turn on VTD
     * @param vtdRoot root folder
     * @param setupName setup name
     * @param projectName project name
     * @param waitTime wait until start vtd to be initalazed
     * @return true if succes
     */
    bool startVtd(const std::string& vtdRoot, const std::string& setupName, const std::string& projectName, float waitTime);

    /**
     * @brief stopVtd turn off VTD
     * @param vtdRoot root folder
     */
    void stopVtd(const std::string& vtdRoot);

    /**
     * @brief proccesTestConfigFile - procces config file
     * @return true if succes
     */
    bool proccesTestConfigFile();

    /**
     * @brief readTestParameter - read test parameters
     * @return true if succes
     */
    bool readTestParameter();

    /**
     * @brief createFolder - create folder
     * @param folderName - folder name
     * @param fileName - file name extension
     * @return true if succes
     */
    bool createFolder(std::string& folderName, const std::string& fileName);

    /**
     * @brief makeApsolute - create apsolute path from relative
     * @param folderName - folder name
     * @return true if succes
     */
    bool makeApsolute(std::string& folderName);

    /**
     * @brief makeImages - start thread for making pucture
     * @param imageGeneratore - class generating images
     */
    void makeImages(boost::scoped_ptr<ImageGenerator> &imageGeneratore, const test_definition::TESTDEFINITION &testDef);

    /**
     * @brief readTestParameters - read test parameters
     * @param testDef - test definition
     * @param pTest -pointer to XML element
     */
    void readTestParameters(test_definition::TESTDEFINITION& testDef, TiXmlElement *pTest);

    bool sendSCPCommand(COMMAND command, VtdApi& api, const double& timeOut);

    void setEnv();

private:
     // buffer for log file
    char buffer [MAX_BUFFER_SIZE];
    // config file
    std::string testConfigFileName_, fileName_;
    // reader class to read XML config file
    VTD::Internal::XMLConfigReader XMLConfigReader_;
    // Test structure
    test_definition::VtdTest vtdTest_;
    // rdbCallback class
    RdbCallback rdbCallback_;
    // thread used for picture writing
    boost::thread imageWrittingThread_;
    // timer for times outs
    Timer timer_;
    // is apply stage
    bool isApplied_;


private:
    /**
     *
     */
    void applyStage();

    bool waitUntilStateReached(OperationStage::Enum state);
};

#endif // MODE1_H
