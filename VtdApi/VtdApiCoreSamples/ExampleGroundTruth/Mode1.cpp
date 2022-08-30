#include "Mode1.h"
#include "LogFile.h"
#include "Test_Helper.h"

#include <iostream>


namespace
{
    static const int NUMBER_OF_ATTEMP = 4;
    static const int TIME_OUT = 60;
    static const double DEFAULT_TEST_TIME = 5.0;
    static const float DEFAULT_FRAME_TIME = 0.033f;
}

using namespace test_definition;
using namespace VTD;

Mode1::Mode1(const std::string& testConfigFileName) :
    testConfigFileName_(testConfigFileName)
  , isApplied_(false)
{
}

Mode1::~Mode1()
{
}

/************************************* READ_CONFIG_FILE *************************************************/
bool Mode1::readConfigFile()
{
    // open config file
    if (!XMLConfigReader_.openXMLFile(testConfigFileName_))
        test_helper::exitTest("Could'not open config file::", false);
    // read test parameter
    if (!readTestParameter())
        test_helper::exitTest("Could'not open config file::", false);
    // create log file
    if (vtdTest_.verbose)
    {
        g_pLogFile->createLogFile(vtdTest_.logFileName.c_str());
        g_pLogFile->fTextOut(BLUE, true, "Configuration test file %s", testConfigFileName_.c_str());
    }
    // procces test config file
    if (!proccesTestConfigFile())
        test_helper::exitTest("Could'not open config file", vtdTest_.verbose);
    // make apsolute path from relative
    if (!makeApsolute(vtdTest_.vtdRootPath))
        test_helper::exitTest("Couldn't create absolute VTD root path\n", vtdTest_.vtdRootPath, vtdTest_.verbose);
    // make apsolute path from relative
    if (!makeApsolute(vtdTest_.hdf5Path))
        test_helper::exitTest("Couldn't create absolute hdf5 files path\n", vtdTest_.hdf5Path, vtdTest_.verbose);
    // make apsolute path from relative
    if (!makeApsolute(vtdTest_.picturePath))
        test_helper::exitTest("Couldn't create absolute png files path\n", vtdTest_.picturePath, vtdTest_.verbose);
    // create folder for hdf5 files
    if (!createFolder(vtdTest_.hdf5Path, "/hdf5_files"))
        test_helper::exitTest("Couldn't create folder for HDF5 files\n", vtdTest_.hdf5Path, vtdTest_.verbose);
    // create folder for pictures files
    if (!createFolder(vtdTest_.picturePath,  "/pictureFiles" ))
        test_helper::exitTest("Couldn't create folder for picture files\n", vtdTest_.picturePath, vtdTest_.verbose);

    return true;
}

/**************************** READ TEST CONFIG FILE HEADER **************************************/
bool Mode1::readTestParameter()
{
    // read config file
    TiXmlElement* pTest;
    TiXmlHandle handleDoc(XMLConfigReader_.getXmlDocument());
    // handler to first root element
    pTest = handleDoc.FirstChildElement().Element();
    // read parameters
    if (!XMLConfigReader_.readAttribute("verbose", pTest, vtdTest_.verbose))
       vtdTest_.verbose = false;

    if (!XMLConfigReader_.readAttribute("writeHdf5", pTest, vtdTest_.writeHdf5))
       vtdTest_.writeHdf5 = false;

    if (!XMLConfigReader_.readAttribute("vtdRoot", pTest, vtdTest_.vtdRootPath))
        return false;

    if (!XMLConfigReader_.readAttribute("logFileName", pTest, vtdTest_.logFileName))
        return false;

    if (!XMLConfigReader_.readAttribute("hdf5path", pTest, vtdTest_.hdf5Path))
        return false;

    if (!XMLConfigReader_.readAttribute("picturePath", pTest, vtdTest_.picturePath))
        return false;

    return true;
}
/**************************** READ TEST PARMETRS *****************************************************/
void Mode1::readTestParameters(TESTDEFINITION& testDef, TiXmlElement *pTest)
{
    if (!XMLConfigReader_.readAttribute("makePictures", pTest, testDef.makePictures))
        testDef.makePictures = false;
#ifdef PNG_ENABLED
    testDef.png = false;
    if (!XMLConfigReader_.readAttribute("png", pTest, testDef.png))
        testDef.png = false;
#endif // PNG_ENABLED
    testDef.tga = false;
    if (!XMLConfigReader_.readAttribute("tga", pTest, testDef.tga))
        testDef.tga = false;

    testDef.raw = false;
    if (!XMLConfigReader_.readAttribute("raw", pTest, testDef.raw))
        testDef.raw = false;

    testDef.bmp = false;
    if (!XMLConfigReader_.readAttribute("bmp", pTest, testDef.bmp))
        testDef.bmp = false;
#ifdef JPEG_ENABLED
    testDef.jpg = false;
    if (!XMLConfigReader_.readAttribute("jpg", pTest, testDef.jpg))
        testDef.jpg = false;
#endif // JPEG_ENABLED
    testDef.csv = false;
    if (!XMLConfigReader_.readAttribute("csv", pTest, testDef.csv))
        testDef.csv = false;

    testDef.hdf5 = false;
#ifdef HDF_ENABLED
    if (!XMLConfigReader_.readAttribute("hdf5", pTest, testDef.hdf5))
        testDef.hdf5 = false;
#endif
    if (!XMLConfigReader_.readAttribute("rdbTrigger", pTest, testDef.rdbTrigger))
        testDef.rdbTrigger = false;

    if (!XMLConfigReader_.readAttribute("testTime", pTest, testDef.testTime))
        testDef.testTime= DEFAULT_TEST_TIME;

    if (!XMLConfigReader_.readAttribute("packageIds", pTest, testDef.filterParameters))
        testDef.filterParameters = "none";
}
/**************************** READ TEST CONFIG FILE *********************************************/
bool Mode1::proccesTestConfigFile()
{
    // TO DO more smaller function
    int numTest = 0, numSetup = 0, numProject = 0, numScenario = 0;
    TiXmlHandle handleDoc(XMLConfigReader_.getXmlDocument());
    TiXmlElement *pTest, *pSetups, *pProjects, *pScenarioList, *pScenario;
    std::vector<std::string> listOfscenarios;
    pTest = handleDoc.FirstChildElement().FirstChildElement().Element();
    std::string buffer;  // string buffer to store data
    // Returns if there is no elements
    if (!pTest)
        return false;
    // tests loop to get all tests
    for (;pTest; pTest = pTest->NextSiblingElement())
    {
        TestDefinition_t testDef;
        readTestParameters(testDef, pTest);
        pSetups = pTest->FirstChildElement();
        if (!pSetups)
            return false;
        // setups loop
        for (; pSetups; pSetups = pSetups->NextSiblingElement())
        {
            if (!XMLConfigReader_.readAttribute("setupName", pSetups, buffer))
                return false;
            // insert setup to setup map
            vtdTest_.setups.insert(std::pair<int, std::string>(numTest, buffer));
            if(testDef.makePictures)
            {
                // if test create picture create shared memories
                if (!XMLConfigReader_.readAttribute("numberOfSharedMem", pSetups, testDef.numOfSharedMemories))
                    return false;
                else
                    testDef.sharedMemoryKeys.resize(0);
                // release flag
                if (!XMLConfigReader_.readAttribute("releaseFlag", pSetups, testDef.releaseFlag))
                    return false;
            }
            // set project loop
            pProjects = pSetups->FirstChildElement();
            if (!pProjects)
                return false;
            // iterator throught projects
            for (; pProjects; pProjects = pProjects->NextSiblingElement())
            {
                if (std::string(pProjects->Value()) == "SharedMemory")
                {
                    unsigned int x;
                    if (!XMLConfigReader_.readAttribute("sharedMemoryKey", pProjects, buffer))
                        return false;

                    test_helper::hex2int(x, buffer.c_str());
                    testDef.sharedMemoryKeys.push_back(x);
                }
                else
                {
                    if (!XMLConfigReader_.readAttribute("projectName", pProjects, buffer))
                        return false;
                    // insert project to map
                    vtdTest_.projects.insert(std::pair<int, std::string>(numSetup, buffer));
                    pScenarioList = pProjects->FirstChildElement();
                    if (!pScenarioList)
                        return false;

                    buffer = pScenarioList->Value();
                    bool testAll = false;
                    if (!XMLConfigReader_.readAttribute("testAll", pScenarioList, testAll))
                       testAll = false;
                    // test all get all test
                    if (testAll)
                    {
                        Internal::FileSystemIO::getAllFilesInDir(vtdTest_.vtdRootPath + "/Data/Projects/" + pProjects->Attribute("projectName") + "/Scenarios/",".xml", listOfscenarios);
                        // get list of all scenarios in folder
                        for (std::vector<std::string>::iterator itr = listOfscenarios.begin(); itr != listOfscenarios.end(); ++itr)
                             vtdTest_.scenarios.insert(std::pair<int, std::string>(numProject, *itr));

                        listOfscenarios.clear();
                    }
                    else
                    {
                        for (; pScenarioList; pScenarioList = pScenarioList->NextSiblingElement())
                        {
                            pScenario = pScenarioList->FirstChildElement();
                            for (; pScenario; pScenario = pScenario->NextSiblingElement())
                            {
                                if (!XMLConfigReader_.readAttribute("name", pScenario, buffer))
                                    return false;

                                vtdTest_.scenarios.insert(std::pair<int, std::string>(numProject, buffer));
                            }
                            // move to next scenario
                            numScenario++;
                        }
                    }
                    // move to next project
                    numProject++;
                }
            }
                // move to next setup
                numSetup++;
        }
        // move to next test
        numTest++;
        vtdTest_.tests.push_back(testDef);
    }
    // return true if all data succesfully have been read
    return true;
}

/************************************* RUN_MODEL ********************************************************/
void Mode1::runMode1()
{
    int setupNum = 0, projectNum = 0, testNum = 0;
    std::string projectName, setupName, scenarioName;
    // Multimap iterators
    std::multimap<int, std::string>::iterator set, pro, sce;
    bool isVtdTurnOn = true;
    Internal::FileSystemIO::setCurrentPath(vtdTest_.vtdRootPath);
    if (vtdTest_.verbose)
        g_pLogFile->fTextOut(BLUE, true, "VTD root folder %s", vtdTest_.vtdRootPath.c_str());


    for (size_t i = 0; i < vtdTest_.tests.size(); ++i)
    {
        if (vtdTest_.verbose)
        {
            sprintf (buffer, "VTD TEST %d", testNum + 1);
            g_pLogFile->writeTopic(buffer, 3);
        }
        // beggining setup position
        for (set = vtdTest_.setups.begin(); set != vtdTest_.setups.end(); ++set)
        {
            // check if setup is pointing to new test
            if (set->first != testNum)
                continue;
            // sto Vtd
            stopVtd(vtdTest_.vtdRootPath);
            if (vtdTest_.verbose)
                g_pLogFile->textOut(BLUE, true, "VTD stopped");

            isVtdTurnOn = false;
            setupName = set->second;
            for (pro = vtdTest_.projects.begin(); pro != vtdTest_.projects.end(); ++pro)
            {
                // check if project is pointing to new setup
                if (pro->first != setupNum)
                    continue;

                projectName = pro->second;
                if (!isVtdTurnOn)
                {
                    // start vtd
                    startVtd(vtdTest_.vtdRootPath, setupName, projectName, TIME_OUT);
                    if (vtdTest_.verbose)
                    {
                        sprintf (buffer, "Test started with setup %s and project %s", setupName.c_str(), projectName.c_str());
                        g_pLogFile->textOut(BLUE, true, buffer);
                    }
                    // check if config stage is applied
                    isApplied_ = rdbCallback_.initVtdApi();
                    if (vtdTest_.verbose)
                    {
                        sprintf (buffer, "SCP communication handle %d", rdbCallback_.generalSCPHandle_);
                        g_pLogFile->textOut(BLUE, true, buffer);
                        sprintf (buffer, "RDB communication handle %d", rdbCallback_.generalRDBHandle_);
                        g_pLogFile->textOut(BLUE, true, buffer);
                    }
                    // applying config stage
                    if (!isApplied_)
                    {
                        applyStage();
                        rdbCallback_.initVtdApi();
                    }
                    // stop, init, load scenario, etc... /* lines added for ubuntu users */
                    sendSCPCommand(STOP, rdbCallback_.vtdApi_, TIME_OUT);
                    rdbCallback_.vtdApi_.changeProject(projectName, vtdTest_.vtdRootPath + "/Data/Projects/" + projectName);
                    rdbCallback_.vtdApi_.loadScenario(vtdTest_.vtdRootPath  + "/Data/Projects/" + projectName + "/Scenarios/" + vtdTest_.scenarios.begin()->second);
                    sendSCPCommand(INIT, rdbCallback_.vtdApi_, TIME_OUT);
                    rdbCallback_.vtdApi_.sendScpCommand("<Display><Database enable=\"true\" streetLamps=\"false\" /><VistaOverlay enable=\"false\" /></Display>");
                    isVtdTurnOn = true;
                }
                else
                {
                    rdbCallback_.vtdApi_.changeProject(projectName, vtdTest_.vtdRootPath + "/Data/Projects/" + projectName);
                }
                    for (sce = vtdTest_.scenarios.begin(); sce != vtdTest_.scenarios.end(); ++sce)
                    {
                        // check if scenario is pointing to new project
                        if (sce->first != projectNum)
                            continue;
                        // get scenario name
                        scenarioName = sce->second;
                        if (vtdTest_.verbose)
                        {
                            sprintf (buffer, "Started scenario %s with setup %s and project %s", scenarioName.c_str(), setupName.c_str(), projectName.c_str());
                            g_pLogFile->writeTopic(buffer, 2);
                        }
                        // run scenario
                        scenarioName = vtdTest_.vtdRootPath  + "/Data/Projects/" + projectName + "/Scenarios/" + sce->second;
                        RunScenarioFile(scenarioName, setupName, projectName, vtdTest_.tests[i]);
                        std::cout << setupName << std::endl;
                        std::cout << projectName << std::endl;
                        std::cout << scenarioName << std::endl;
                    }
                    // move to nect project
                    projectNum++;
                }
            // move to next setup
            setupNum++;
            if (isVtdTurnOn)
            {
                // turn off vtd to start new setup
                rdbCallback_.closeVtdApi();
                stopVtd(vtdTest_.vtdRootPath);
                isVtdTurnOn = false;
            }
        }
        // move to next test
        testNum++;
    }

    if (vtdTest_.verbose)
        g_pLogFile->writeTopic("All tests completed ", 2);
    // close log file
    g_pLogFile->Del();
    std::cout << "Stopping VTD.........................." << std::endl;
    stopVtd(vtdTest_.vtdRootPath);
    std::cout << "Exiting..............................." << std::endl;
}

/**************************** RUN_AND_AUTO_ENE_SCENARIO *************************************************/
void Mode1::RunAndAutoEndScenario(const TestDefinition_t& testDefinition_t)
{
    // create image genarator instance
    boost::scoped_ptr<ImageGenerator> imagenerator(new ImageGenerator (testDefinition_t.sharedMemoryKeys
                                                                       , testDefinition_t.releaseFlag
                                                                       , vtdTest_.picturePath + "/" + fileName_));
    // Send start commeand
    if (!sendSCPCommand(START, rdbCallback_.vtdApi_, TIME_OUT))
    {
        g_pLogFile->fTextOut(RED, true, "Simulation couldn't be started timeout error after %d sec", TIME_OUT);
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return;
    }
    // open hdf5 file
    if (!rdbCallback_.openFile(fileName_, vtdTest_.hdf5Path))
    {
        g_pLogFile->fTextOut(RED, true, "Couldn't open file %s", fileName_.c_str());
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return;
    }
    // make pictures
    if (testDefinition_t.makePictures)
    {
        imagenerator->initSharedMemory();
        imageWrittingThread_ = boost::thread(&Mode1::makeImages, this, boost::ref(imagenerator), boost::ref(testDefinition_t));
    }

    if (vtdTest_.verbose)
    {
        std::cout << "Simulation started...............\n";
        g_pLogFile->textOut(BLUE, true, "Simulation started");
    }
    // offest to give enough time for picture writing
    unsigned int timeOffset = boost::numeric_cast<unsigned int>( testDefinition_t.sharedMemoryKeys.size() ) + 1;
    double maximumSimulationtime = NUMBER_OF_ATTEMP * testDefinition_t.testTime * timeOffset;
    // start timer
    timer_.start();
    while ((rdbCallback_.getSimulationTime() < testDefinition_t.testTime)
          && (timer_.elapsedSeconds() < maximumSimulationtime)
          && (rdbCallback_.vtdApi_.getOperationStage() == OperationStage::RUN || rdbCallback_.vtdApi_.getOperationStage() == OperationStage::READY))
    {
       if(testDefinition_t.rdbTrigger && imagenerator->getAllPictureWritten_())
       {
           rdbCallback_.vtdApi_.sendTriggerRDB(rdbCallback_.generalRDBHandle_, DEFAULT_FRAME_TIME, 0, 0);
           // make enough time to all bilders to be written
           test_helper::SecDelay(  DEFAULT_FRAME_TIME * boost::numeric_cast<float>( timeOffset ) );
       }
       rdbCallback_.vtdApi_.update(3);
    }
    // stop writing images
    if (testDefinition_t.makePictures)
    {
       imagenerator->stop();
       if (imageWrittingThread_.joinable())
           imageWrittingThread_.join();
    }
    
    // check if runing time is went out
    if ( timer_.elapsedSeconds() >= maximumSimulationtime )
    {
         std::cout << "Simulation started but some of VTD components probably stop running" << std::endl;
         g_pLogFile->textOut(RED, true, "Simulation started but some of VTD components probably stop running");
         g_pLogFile->textOut(RED, true, "TEST ABORTED");
         return;
    }
    // check if operation stage is run
    if ( rdbCallback_.vtdApi_.getOperationStage() != OperationStage::RUN )
    {
        std::cout << "Operation stage change from RUN to other simulation stage, simulation stopped" << std::endl;
        g_pLogFile->textOut(RED, true, "Operation stage change from RUN to other simulation stage, simulation stopped");
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return;
    }
    // stop timer and close file
    timer_.stop();
    rdbCallback_.closeFile();
    // stop simullation
    if (!sendSCPCommand(STOP, rdbCallback_.vtdApi_, TIME_OUT))
    {
        g_pLogFile->fTextOut(RED, true, "Simulation couldn't be stopped timeout error after %d sec", TIME_OUT);
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return;
    }
    // write info to log file
    if (vtdTest_.verbose)
    {
        g_pLogFile->textOut(BLUE, true, "Simulation stopped");
        g_pLogFile->writeTopic("Scenario completed ", 2);
    }

    std::cout << "Exit recording:::::::::::::::..\n";
}

/**************************** INIT SCENARIO ****************************************************/
bool Mode1::InitScenario()
{
    // init scenario
    std::cout << "Initializing scenario." << std::endl;
    if (!sendSCPCommand(INIT, rdbCallback_.vtdApi_, TIME_OUT))
    {
        g_pLogFile->fTextOut(RED, true, "Simulation couldn't be initalazed timeout error after %d sec", TIME_OUT);
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return false;
    }

    if (vtdTest_.verbose)
    {
        std::cout << "Scenario initialized\n";
        g_pLogFile->textOut(BLUE, true, "Scenario initialized");
    }
    // added on testing department request to have same enverment during all tests
    setEnv();
    return true;
}

/**************************** RUN SCENARIO FILE ****************************************************/
void Mode1::RunScenarioFile(  const std::string& scenarioFileName
                            , const std::string& setupFileName
                            , const std::string& projectFileName
                            , const TestDefinition_t& testDefinition_t)
{
    // stop scenario
    std::cout << "Stopping scenario " << scenarioFileName << std::endl;
    if (!sendSCPCommand(STOP, rdbCallback_.vtdApi_, TIME_OUT))
    {
        g_pLogFile->fTextOut(RED, true, "Simulation couldn't be stopped timeout error after %d sec", TIME_OUT);
        g_pLogFile->textOut(RED, true, "TEST ABORTED");
        return;
    }
    // set filter
    rdbCallback_.populateFilter(testDefinition_t.filterParameters);
    if (vtdTest_.verbose)
    {
        g_pLogFile->textOut(BLUE, true, "Simulation stopped");
    }
    // load scenario
    std::cout << "Loading scenario " << scenarioFileName << std::endl;
    rdbCallback_.vtdApi_.loadScenario(scenarioFileName);
    if (vtdTest_.verbose)
    {
        sprintf (buffer, "Scenario %s loaded", scenarioFileName.c_str());
        g_pLogFile->textOut(BLUE, true, buffer);
    }
    // init scenario
    if(!InitScenario())
        return;

    std::cout << "Starting scenario " << scenarioFileName << std::endl;
    fileName_ = setupFileName + "_" + projectFileName + "_" + Internal::FileSystemIO::getFileNameFromPath(scenarioFileName);
    rdbCallback_.setFileName(scenarioFileName);
    RunAndAutoEndScenario(testDefinition_t);
    std::cout << "Scenario " << scenarioFileName << " terminated" << std::endl;
}

/**************************** START VTD **********************************************************/
bool Mode1::startVtd(const std::string& vtdRoot
                     , const std::string& setupName
                     , const std::string& projectName
                     , float waitTime)
{
    // TO DO switch to boost procces since system call could lock up system
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork faild.\n");
        exit(1);
    }
    else if (pid == 0)
    {
       std::string fileName = vtdRoot + "/bin/vtdStart.sh -project=" + projectName + " -setup=" + setupName +  " -autoConfig";
       if (system(fileName.c_str()) != 0)
       {
           std::cout << "Could not start VTD: " << strerror(errno) << std::endl;
           if (vtdTest_.verbose)
           {
                g_pLogFile->fTextOut("Could not start VTD: %s \n", strerror(errno));
                g_pLogFile->textOut("Program will not executed without valid root path. \n");
                g_pLogFile->textOut( "Please enter valid root path to command line.");
           }
           // exit from test
           test_helper::exitTest("Could not start VTD: ", fileName, vtdTest_.verbose);
           return false;
       }
       else
       {
           if (vtdTest_.verbose)
               g_pLogFile->fTextOut("Command executed %s \n", fileName.c_str());

           test_helper::SecDelay(waitTime);
           exit(5);
       }
    }
    if (vtdTest_.verbose)
        g_pLogFile->textOut("VTD succesefully started \n");

    test_helper::SecDelay(waitTime);
    return true;
}

/**************************** STOP VTD **********************************************************/
void Mode1::stopVtd(const std::string& vtdRoot)
{
    // TO DO switch to boost procces since system call could lock up system
    std::string fileName = vtdRoot + "/bin/vtdStop.sh";
    if (system(fileName.c_str()) < 0)
        std::cout << "Could not stop VTD: " << strerror(errno) << std::endl;

    // delay one sec
    test_helper::SecDelay(1.0f);
}



/********************************* CREATE FOLDER *****************************************************/
bool Mode1::createFolder(std::string& folderName, const std::string& fileName)
{
    folderName.append(fileName);
    // check if folder exist if not create new one
    if (!Internal::FileSystemIO::checkIfFolderExist(folderName))
    {
        std::cout << "Provided path does not exist: " << folderName << std::endl;
        if(!Internal::FileSystemIO::createFolder(folderName))
            return false;
    }

    return true;
}

/********************************* MAKE APSOLUTE PATH *****************************************************/
bool Mode1::makeApsolute(std::string& folderName)
{
    return Internal::FileSystemIO::makeAbsolutePathFromRelative(folderName);
}

/**************************** MAKE IMAGES ************************************************************/
void Mode1::makeImages(boost::scoped_ptr<ImageGenerator>& imageGeneratore, const TESTDEFINITION &testDef)
{
    if (testDef.raw)
        imageGeneratore->setPictureType(RdbImageIO::FileFormat::RawData);
#ifdef PNG_ENABLED
    else if (testDef.png)
        imageGeneratore->setPictureType(RdbImageIO::FileFormat::PNG);
#endif //PNG_ENABLED
    else if  (testDef.tga)
         imageGeneratore->setPictureType(RdbImageIO::FileFormat::TGA);
    else if  (testDef.bmp)
         imageGeneratore->setPictureType(RdbImageIO::FileFormat::BMP);
#ifdef JPEG_ENABLED
    else if  (testDef.jpg)
         imageGeneratore->setPictureType(RdbImageIO::FileFormat::JPG);
#endif  //JPEG_ENABLED
    else if  (testDef.csv)
         imageGeneratore->setPictureType(RdbImageIO::FileFormat::CSV);
//TODO: Due to circular dependencies this is being deactivated for now, and will be replaced by a better solution later on.
//TODO: To write images into HDF files please use the WriteHdf5Image class from VtdHdf5 directly
//#ifdef HDF_ENABLED
//    else if  (testDef.hdf5)
//         imageGeneratore->setPictureType(RdbImageIO::FileFormat::HDF5);
//#endif
    // run picture creation
    imageGeneratore->run();
    std::cout << "Stop make images function..............\n";
}

/**************************** ApplyStage *****************************************************/
void Mode1::applyStage()
{

    test_helper::SecDelay(3.0);
    rdbCallback_.vtdApi_.update();
    int number_of_attemp = 0;
    OperationStage::Enum operStage = rdbCallback_.vtdApi_.getOperationStage();

    while (operStage != OperationStage::READY && number_of_attemp  < NUMBER_OF_ATTEMP)
    {
        if (operStage == OperationStage::CONFIG)
        {
            rdbCallback_.vtdApi_.applyConfiguration(/*startByScript*/ false, /*isBlocking*/ false);
            if(vtdTest_.verbose)
                g_pLogFile->fTextOut("Apply configuration %d time.......", number_of_attemp);

            test_helper::SecDelay(10.0);
            rdbCallback_.vtdApi_.update();
            operStage =  rdbCallback_.vtdApi_.getOperationStage();
            if (operStage != OperationStage::READY)
                test_helper::SecDelay(20.0);
        }
        else if (operStage == OperationStage::UNDEFINED)
        {
            rdbCallback_.vtdApi_.enterConfigurationStage(false);
            if(vtdTest_.verbose)
                g_pLogFile->fTextOut("Enter configuration stage %d time.................... \n", number_of_attemp);

            test_helper::SecDelay(2.0);
        }

        test_helper::SecDelay(0.5);
        rdbCallback_.vtdApi_.update();
        operStage =  rdbCallback_.vtdApi_.getOperationStage();
        ++number_of_attemp;
    }

    if (number_of_attemp == NUMBER_OF_ATTEMP)
    {
        if(vtdTest_.verbose)
            test_helper::exitTest("TEST::ERROR::Could'n apply configuration stage....................", vtdTest_.verbose);

        std::cout << "MAIN::ERROR::Could'n apply configuration stage" << std::endl;
        exit(2);
    }
}

bool Mode1::sendSCPCommand(COMMAND command, VtdApi& api, const double& timeOut)
{
    // TO DO with conditional variables
    bool isCommandSucSend = false;
    switch (command)
    {
        case STOP:
        {
            api.stopSimulation(/*isBlocking*/ false);
            timer_.start();
            while (api.getOperationStage() != OperationStage::READY && timer_.elapsedSeconds() < timeOut)
            {
                api.stopSimulation(/*isBlocking*/ false);
                api.update();
                test_helper::SecDelay(0.5);
            }

            if (api.getOperationStage() == OperationStage::READY)
                isCommandSucSend = true;

            timer_.stop();
        }break;

        case INIT:
        {
            api.initSimulation(VtdApi::OperationMode::OPERATION, false);
            timer_.start();
            while (OperationStage::INITDONE != api.getOperationStage() &&  timer_.elapsedSeconds() < timeOut)
            {
                api.initSimulation(VtdApi::OperationMode::OPERATION, false);
                api.update();
                test_helper::SecDelay(1.5);
            }

            if (api.getOperationStage() == OperationStage::INITDONE)
                isCommandSucSend = true;

            timer_.stop();

        }break;

        case START:
        {
            api.startSimulation(VtdApi::OperationMode::OPERATION, -1.0f, false);
            timer_.start();
            api.update();
            test_helper::SecDelay(0.5);
            while (api.getOperationStage() != OperationStage::RUN && timer_.elapsedSeconds() < timeOut)
            {
                api.startSimulation(VtdApi::OperationMode::OPERATION, -1.0f, false);
                api.update();
                test_helper::SecDelay(0.5);
            }

            if (api.getOperationStage() == OperationStage::RUN)
                isCommandSucSend = true;

            timer_.stop();
        }break;
        case LOAD_SCENARIO:
            break;
        default:
            break;
    }

     return isCommandSucSend;
}

void  Mode1::setEnv()
{
    const std::string command = "<Environment><Friction value=\"1.000000\" /><Date day=\"1\" month=\"6\" year=\"2008\" /><TimeOfDay headlights=\"auto\" timezone=\"0\" value=\"50400\" /><Sky cloudState=\"0/8\" visibility=\"100000.000000\" /><Precipitation intensity=\"0.000000\" type=\"none\" /><Road effectScale=\"0.500000\" state=\"dry\" /></Environment>";

    rdbCallback_.vtdApi_.sendScpCommand(command);
}
