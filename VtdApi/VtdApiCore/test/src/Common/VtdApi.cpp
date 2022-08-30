#include "RdbReceiverMock.h"
#include "VtdApi/VtdApi.h"

#include <VtdToolkit/Scp/ScpBuilder.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <boost/filesystem.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include <cstdio>
#include <string>

namespace
{
    const std::string DEFAULT_HOST = "127.0.0.1";
    const std::string TEST_PLAYER_NAME = "TestPlayer";
    const std::string EGO_NAME = "Ego";
    const unsigned int TEST_NUMBER = 100;
    const unsigned int UPDATE_TIME = 33;
}

using namespace VTD;

namespace fs = boost::filesystem;

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class VtdApiMock : public VtdApi
{
  public:
    MOCK_METHOD2(connectSCP, ConnectionHandle(const std::string& hostname, unsigned int scpPortNumber));
    MOCK_METHOD1(disconnectSCP, bool(ConnectionHandle& handle));
    MOCK_METHOD3(connectRDB, ConnectionHandle(const std::string& hostname, unsigned int rdbPortNumber, Protocols::Enum rdbProtocol));
    MOCK_METHOD1(disconnectRDB, bool(ConnectionHandle& handle));
    MOCK_CONST_METHOD1(isConnected, bool(const ConnectionHandle& handle));
};
/**
 * @brief The MyVtdApi class - use to test api
 */
class MyVtdApi : public ::testing::Environment
{
  VtdApi & vtdApi_;
  public:
    MyVtdApi (VtdApi & vtdApi) : vtdApi_(vtdApi){}

    ConnectionHandle connectScp()
    {
        return vtdApi_.connectSCP(DEFAULT_HOST, DEFAULT_RDB_PORT);
    }

    ConnectionHandle connectRdb(Protocols::Enum protocol)
    {
        ConnectionHandle handle;

        switch (protocol)
        {
            case Protocols::RDB_UDP:
            {
                handle = vtdApi_.connectRDB(DEFAULT_HOST, DEFAULT_UDP_RX_PORT, protocol);
                return handle;
            }break;

            case Protocols::RDB_TCP:
            {
                handle = vtdApi_.connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, protocol);
                return handle;
            }break;


        default:
            break;
        }
    }

    bool disconnectSCP(ConnectionHandle& handle)
    {
        handle = vtdApi_.disconnectSCP(handle);

        return handle;
    }

    bool disconnectRDB(ConnectionHandle& handle)
    {
        handle = vtdApi_.disconnectRDB(handle);

        return handle;
    }

    bool isConnected(ConnectionHandle& handle)
    {
        return vtdApi_.isConnected(handle);
    }

};

TEST(VtdApiMockTest, connectSCP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    EXPECT_CALL(vtdApi, connectSCP(DEFAULT_HOST, DEFAULT_RDB_PORT)).Times(1).WillOnce(Return(TEST_NUMBER));
    ConnectionHandle handle = myVtdApi.connectScp();
    EXPECT_EQ(handle, TEST_NUMBER);
}

TEST(VtdApiMockTest, disconnectSCP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    ConnectionHandle handle;
    EXPECT_CALL(vtdApi, disconnectSCP(handle)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(myVtdApi.disconnectSCP(handle));
}

TEST(VtdApiMockTest, dis_connectSCP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    EXPECT_CALL(vtdApi, connectSCP(DEFAULT_HOST, DEFAULT_RDB_PORT)).Times(1).WillOnce(Return(TEST_NUMBER));
    ConnectionHandle handle = myVtdApi.connectScp();
    EXPECT_EQ(handle, TEST_NUMBER);
    EXPECT_CALL(vtdApi, disconnectSCP(handle)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(myVtdApi.disconnectSCP(handle));
}

TEST(VtdApiMockTest, connectRDB_UDP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    EXPECT_CALL(vtdApi, connectRDB(DEFAULT_HOST, DEFAULT_UDP_RX_PORT, Protocols::RDB_UDP)).Times(1).WillOnce(Return(TEST_NUMBER));
    ConnectionHandle handle = myVtdApi.connectRdb(Protocols::RDB_UDP);
    EXPECT_EQ(handle, TEST_NUMBER);
}

TEST(VtdApiMockTest, connectRDB_TCP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    EXPECT_CALL(vtdApi, connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP)).Times(1).WillOnce(Return(TEST_NUMBER));
    ConnectionHandle handle = myVtdApi.connectRdb(Protocols::RDB_TCP);
    EXPECT_EQ(handle, TEST_NUMBER);
}

TEST(VtdApiMockTest, connectRDB_UDP_TCP)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    EXPECT_CALL(vtdApi, connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP)).Times(1).WillOnce(Return(TEST_NUMBER));
    ConnectionHandle handle = myVtdApi.connectRdb(Protocols::RDB_TCP);
    EXPECT_EQ(handle, TEST_NUMBER);
    EXPECT_CALL(vtdApi, connectRDB(DEFAULT_HOST, DEFAULT_UDP_RX_PORT, Protocols::RDB_UDP)).Times(1).WillOnce(Return(TEST_NUMBER));
    handle = myVtdApi.connectRdb(Protocols::RDB_UDP);
    EXPECT_EQ(handle, TEST_NUMBER);
}

TEST(VtdApiMockTest, disconnectRDB)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    ConnectionHandle handle;
    EXPECT_CALL(vtdApi, disconnectRDB(handle)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(myVtdApi.disconnectRDB(handle));
}

TEST(VtdApiMockTest, isConnected)
{
    VtdApiMock vtdApi;
    MyVtdApi myVtdApi(vtdApi);
    ConnectionHandle handle;
    EXPECT_CALL(vtdApi, isConnected(handle)).Times(1).WillOnce(Return(true));
    EXPECT_TRUE(myVtdApi.isConnected(handle));
}

TEST(VtdApiTest, TimeOut)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    bool test = api->waitUntilStateReached(OperationStage::RUN, 10.0);
    EXPECT_FALSE(test);
}

TEST(VtdApiTest, StoptVtd)
{
    fs::current_path(fs::system_complete(fs::path(g_command_line_arg)));
    // Stopt Vtd
    std::string fileName = "bin/vtdStop.sh";
    EXPECT_NE(system(fileName.c_str()), -1);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
}

TEST(VtdApiTest, StartVtd)
{
    // Start Vtd
    std::string fileName = g_command_line_arg + "bin/vtdStart.sh -project=SampleProject -setup=Standard -autoConfig >& debug.txt";
    EXPECT_GT(system(fileName.c_str()), -1);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(20000));
}

TEST(VtdApiTest, configTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    api->update(UPDATE_TIME);
    if(api->getOperationStage() != OperationStage::CONFIG)
    {
        api->enterConfigurationStage(true);
        boost::this_thread::sleep_for(boost::chrono::microseconds(1000000));
    }
    api->update(UPDATE_TIME);
    EXPECT_EQ(OperationStage::CONFIG, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, applyTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->update(UPDATE_TIME);
    api->applyConfiguration();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    api->update(UPDATE_TIME);
    EXPECT_EQ(OperationStage::READY, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);

    // TODO [BB]; for successful testing we need to use the task state check, which is not implemented yet
}

TEST(VtdApiTest, changeProjectTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->changeProject("SampleProject", "IsThisNecessary?");
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);

    // TODO [BB]; for successful testing we need to use the task state check, which is not implemented yet
}

TEST(VtdApiTest, loadScenarioTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->loadScenario("Crossing8Demo.xml");
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
    // TODO [BB]; for successful testing we need to use the task state check, which is not implemented yet
}

TEST(VtdApiTest, initTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->update(UPDATE_TIME);
    api->loadScenario("Crossing8Demo.xml");
    api->update(UPDATE_TIME);
    api->initSimulation();
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    api->update(UPDATE_TIME);
    OperationStage::Enum i = api->getOperationStage();
    EXPECT_TRUE(OperationStage::INITDONE == api->getOperationStage() || OperationStage::READY == api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, isInitializedTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    EXPECT_TRUE(api->isSimulationInitialized());
}

TEST(VtdApiTest, getOperationStage)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    EXPECT_NE(api->getOperationStage(), -1);
}

TEST(VtdApiTest, stopTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    api->stopSimulation();
    api->update(UPDATE_TIME);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    EXPECT_EQ(OperationStage::READY, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);

}

TEST(VtdApiTest, startTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->startSimulation();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    api->update(UPDATE_TIME);
    EXPECT_EQ(OperationStage::RUN, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);

    // TODO [BB]; for successful testing we need to use the task state check, which is not implemented yet
}

TEST(VtdApiTest, TimeOut2)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    bool test = api->waitUntilStateReached(OperationStage::RUN, 10.0);
    EXPECT_TRUE(test);
}

TEST(VtdApiTest, stopTestAfterStart)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    api->stopSimulation();
    api->update(UPDATE_TIME);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    EXPECT_EQ(OperationStage::READY, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);

}

TEST(VtdApiTest, startTestSecondTime)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->startSimulation();
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    api->update(UPDATE_TIME);
    EXPECT_EQ(OperationStage::RUN, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, createPlayerVehicleTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test if player vehicle have been created    */
    /*******************************************************************************************/
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->createPlayerVehicle(TEST_PLAYER_NAME);
    api->queryPlayerName(TEST_PLAYER_NAME);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, deletePlayerVehicleTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test if player vehicle have been deleted    */
    /*******************************************************************************************/
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->deletePlayerVehicle(TEST_PLAYER_NAME);
    api->queryPlayerName(TEST_PLAYER_NAME);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, setPlayerVehicleSpeedTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test player vehicle speed                   */
    /*******************************************************************************************/
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->setPlayerVehicleSpeed(TEST_PLAYER_NAME, 60);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, setPlayerVehicleSpeedRelativeTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test player vehicle speed                   */
    /*******************************************************************************************/
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->setPlayerVehicleSpeedRelative(TEST_PLAYER_NAME, EGO_NAME, 20);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, setPlayerVehiclePosInertialTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test player position                        */
    /*******************************************************************************************/
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    VTD::Vec3 position(10.0, 10.0, 10.0);
    api->setPlayerVehiclePosInertial(TEST_PLAYER_NAME, position, position);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, setPlayerVehiclePosRelativeTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test player position                        */
    /*******************************************************************************************/
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    VTD::Vec3 position(10.0, 10.0, 10.0);
    api->setPlayerVehiclePosRelative(TEST_PLAYER_NAME, EGO_NAME, position, position, true);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, setPlayerVehiclePosRelativeRoadTest)
{
    /*******************************************************************************************/
    /* To create set of query callback which could test player position                        */
    /*******************************************************************************************/
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->setPlayerVehiclePosRelativeRoad(TEST_PLAYER_NAME, EGO_NAME, 10.0, 1.0, 10.0, 1.0);
    EXPECT_TRUE(0 != 0); // TODO [BB]: The whole method hasn't been tested
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, pauseTest)
{// TODO [BB]: Don't mess around with PAUSE and/or STEP, it fucks up VTD
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->pauseSimulation();
    api->update(UPDATE_TIME);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    EXPECT_EQ(OperationStage::PAUSE, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, stepTest)
{  // TODO [BB]: Don't mess around with PAUSE and/or STEP, it fucks up VTD
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->stepSimulation(100); // TODO [BB]: not sure about the expected behaviour, step size of 100 shows

    // every of the next 100 frames and then the simulation stops
    // TODO [BB]; for successful testing we need to use the task state check, which is not implemented yet
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, restartTest)
{
       boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->restartSimulation();
    api->update(UPDATE_TIME);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
    EXPECT_EQ(OperationStage::RUN, api->getOperationStage());
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, syncTestSCP)
{
    const float deltaT = 0.016f;
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    EXPECT_TRUE(api->isConnected(handle));
    api->sendSyncSignalSCP();
    const unsigned int totalAttempts = 60;
    unsigned int successCount = 0;
    unsigned int count = 0;
    while(count++ < totalAttempts)
    {
        EXPECT_NO_THROW(api->sendSyncSignalSCP());
        boost::this_thread::sleep_for(boost::chrono::milliseconds(static_cast<UInt64>(deltaT*1000.0f)));
        ++successCount;
    }
    EXPECT_EQ(totalAttempts, successCount);
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
}

TEST(VtdApiTest, syncTestRDB)
{
    const float deltaT = 0.016f;

    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle handle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    ConnectionHandle rdbHandle = api->connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT);

    EXPECT_NE(rdbHandle, 0);
    EXPECT_NE(rdbHandle, handle);
    EXPECT_TRUE(api->isConnected(handle));
    EXPECT_TRUE(api->isConnected(rdbHandle));
    EXPECT_NO_THROW(api->sendSyncSignalRDB(rdbHandle, deltaT, deltaT, 1));

    const unsigned int totalAttempts = 60;
    unsigned int successCount = 0;
    unsigned int count = 0;
    while(count++ < totalAttempts)
    {
        EXPECT_NO_THROW(api->sendSyncSignalRDB(rdbHandle, deltaT, count*deltaT, count));
        boost::this_thread::sleep_for(boost::chrono::milliseconds(static_cast<UInt64>(deltaT * 1000.0f)));
        successCount++;
    }
    EXPECT_EQ(totalAttempts, successCount);
    api->disconnectSCP(handle);
    EXPECT_FALSE(handle);
    // [GK] an integration test should check if the trigger is interpreted by VTD
}

TEST(VtdApiTest, DISABLED_rdbUDPTest)
{
    //placeholder
    EXPECT_TRUE(false);
}

TEST(VtdApiTest, DISABLED_rdb_multiconnectTest)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle scpHandle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    ConnectionHandle rdbHandle = api->connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);
    RdbReceiverMock receiver(api.get(), scpHandle, rdbHandle);
    EXPECT_NE(rdbHandle, scpHandle);
    EXPECT_TRUE(api->isConnected(scpHandle));
    EXPECT_TRUE(api->isConnected(rdbHandle));
    api->disconnectRDB(rdbHandle);
    api->disconnectSCP(scpHandle);
    EXPECT_FALSE(scpHandle);
    EXPECT_FALSE(rdbHandle);
}

TEST(VtdApiTest, RdbMessageReceiveSigSlot)
{
    boost::unique_ptr<VtdApi> api(new VtdApi);
    ConnectionHandle scpHandle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
    ConnectionHandle rdbHandle = api->connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);
    RdbReceiverMock receiver(api.get(), scpHandle, rdbHandle);
    EXPECT_NE(rdbHandle, scpHandle);
    EXPECT_TRUE(api->isConnected(scpHandle));
    EXPECT_TRUE(api->isConnected(rdbHandle));
    int attempt = 0;
    while (attempt < 1000)
    {
        EXPECT_NO_THROW(api->update(UPDATE_TIME));
        ++attempt;
    }

    EXPECT_TRUE(receiver.getIsRdbReceived());
    EXPECT_TRUE(receiver.getIsScpReceived());
    api->disconnectRDB(rdbHandle);
    api->disconnectSCP(scpHandle);
    EXPECT_FALSE(scpHandle);
    EXPECT_FALSE(rdbHandle);
}

TEST (vtdApiTest, disconectTest)
{
    for (int i = 0; i < 100; ++i)
    {
        boost::unique_ptr<VtdApi> api(new VtdApi);
        ConnectionHandle scpHandle = api->connectSCP(DEFAULT_HOST, DEFAULT_SCP_PORT);
        ConnectionHandle rdbHandle = api->connectRDB(DEFAULT_HOST, DEFAULT_RDB_PORT, Protocols::RDB_TCP);
        RdbReceiverMock receiver(api.get(), scpHandle, rdbHandle);
        api->update(3);
        api->disconnectRDB(rdbHandle);
        api->disconnectSCP(scpHandle);
        EXPECT_FALSE(scpHandle);
        EXPECT_FALSE(rdbHandle);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(10));
    }
}

