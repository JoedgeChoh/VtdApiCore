#include <iostream>
#include <gtest/gtest.h>
#include <math.h>

#include <VtdHdf5/Hdf5RdbMessageHeader.h>
#include <VtdHdf5/WriteHdf5Data.h>
#include <VtdToolkit/viRDBIcd.h>
#include <VtdHdf5/RDBHDF5lib.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

/*
 * Just test for header data
*/
void  printHeader(const RDB_MSG_HDR_t& rdbMessageHeader)
{
    std::cout << "***************** TEST RESULTS ************************" << std::endl;
    std::cout << "magicNo " << rdbMessageHeader.magicNo << std::endl
              << "version " << rdbMessageHeader.version << std::endl
              << "headerSize " << rdbMessageHeader.headerSize << std::endl
              << "dataSize " << rdbMessageHeader.dataSize << std::endl
              << "frameNo " << rdbMessageHeader.frameNo << std::endl
              << "simTime " << rdbMessageHeader.simTime << std::endl;
    std::cout << "*******************************************************" << std::endl;
}

struct RdbMessageHeader : public RdbToHdf5Writer::Hdf5RdbMessageHeader
{
    uint16_t  magicNo;
    uint16_t  version;
    uint32_t  headerSize;
    uint32_t  dataSize;
    uint32_t  frameNo;
    double    simTime;

    RdbMessageHeader(){}

    void initHeader(uint16_t  magicNo, uint16_t  version, uint32_t  headerSize, uint32_t  dataSize, uint32_t  frameNo, double simTime)
    {
        this->magicNo = magicNo;
        this->version = version;
        this->headerSize = headerSize;
        this->dataSize = dataSize;
        this->frameNo = frameNo;
        this->simTime = simTime;
    }
};

struct RdbMessageHeaderTest : testing::Test
{
    boost::shared_ptr<RdbMessageHeader> rdbMessageHeader_;

    RdbMessageHeaderTest()
    {
        rdbMessageHeader_ = boost::shared_ptr<RdbMessageHeader> (new RdbMessageHeader);
    }
};

struct RdbMessageHeaderState
{

        uint16_t  initial_magicNo;
        uint16_t  initial_version;
        uint32_t  initial_headerSize;
        uint32_t  initial_dataSize;
        uint32_t  initial_frameNo;
        double    initial_simTime;

        friend std::ostream& operator <<(std::ostream& os, const RdbMessageHeaderState& rdbMessageHeaderState)
        {
            return os   << "***************** INITIAL VALUES ************************" << std::endl
                        << "initial_magicNo " << rdbMessageHeaderState.initial_magicNo << std::endl
                        << "initial_version " << rdbMessageHeaderState.initial_version << std::endl
                        << "initial_headerSize " << rdbMessageHeaderState.initial_headerSize << std::endl
                        << "initial_dataSize " << rdbMessageHeaderState.initial_dataSize << std::endl
                        << "initial_frameNo " << rdbMessageHeaderState.initial_frameNo << std::endl
                        << "initial_simTime " << rdbMessageHeaderState.initial_simTime << std::endl
                        << "***************** INITIAL VALUES ************************" << std::endl ;
        }



};

struct RdbMessageHeaderWriteTest : RdbMessageHeaderTest, testing::WithParamInterface<RdbMessageHeaderState>
{
    RdbMessageHeaderWriteTest()
    {
        rdbMessageHeader_->magicNo = GetParam().initial_magicNo;
    }
};

TEST_P(RdbMessageHeaderWriteTest, writeHeader)
{
      RdbMessageHeaderState as = GetParam();
      rdbMessageHeader_->initHeader(as.initial_magicNo, as.initial_version, as.initial_headerSize, as.initial_dataSize, as.initial_frameNo, as.initial_simTime);
      RdbToHdf5Writer::WriteHdf5Data rdbToHdf5Writer_;
      RDB_MSG_t msg, msg1;

      msg.hdr.magicNo = as.initial_magicNo;
      msg.hdr.version = as.initial_version;
      msg.hdr.headerSize = as.initial_headerSize;
      msg.hdr.dataSize = as.initial_dataSize;
      msg.hdr.frameNo = as.initial_frameNo;
      msg.hdr.simTime = as.initial_simTime;

      rdbToHdf5Writer_.openHdf5File("/tmp/testHeading");
      rdbToHdf5Writer_.writeHeader(msg.hdr);
      rdbToHdf5Writer_.writeHeader(msg.hdr);
      rdbToHdf5Writer_.closeHdf5File();

      std::cout << as;

       hid_t fileId = H5Fopen("/tmp/testHeading.h5", H5F_ACC_RDONLY, H5P_DEFAULT);

       H5TBread_records(fileId, RdbToHdf5Writer::MESSAGE_HEADER_TABLE_NAME , 0, 1
          , rdbMessageHeader_.get()->dstSize_, rdbMessageHeader_.get()->dstOffset_
          , rdbMessageHeader_.get()->dstSizes_, &msg1);

       H5Fclose(fileId);
      printHeader (msg1.hdr);

      EXPECT_EQ(as.initial_dataSize, msg1.hdr.dataSize);
      EXPECT_EQ(as.initial_magicNo, msg1.hdr.magicNo);
      EXPECT_EQ(as.initial_headerSize, msg1.hdr.headerSize);
      EXPECT_EQ(as.initial_version, msg1.hdr.version);
      EXPECT_EQ(as.initial_frameNo, msg1.hdr.frameNo);
      EXPECT_EQ(as.initial_simTime, msg1.hdr.simTime);

}

INSTANTIATE_TEST_CASE_P(Default
                        , RdbMessageHeaderWriteTest
                        , testing::Values(RdbMessageHeaderState{RDB_MAGIC_NO, RDB_VERSION, sizeof(RDB_MSG_HDR_t), 10, 10, 10.5}
                                          , RdbMessageHeaderState{RDB_MAGIC_NO, RDB_VERSION, sizeof(RDB_MSG_HDR_t), 14, 10, 10.5}
                                          , RdbMessageHeaderState{RDB_MAGIC_NO, RDB_VERSION, sizeof(RDB_MSG_HDR_t), 14, 10, 10.5}));






