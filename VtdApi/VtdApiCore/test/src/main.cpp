#include <gtest/gtest.h>
#include "Common/RdbReceiverMock.h"

int main(int argc, char** argv)
{
    if (argc < 1)
        return 0;

    std::string command_line(argc == 2 ? argv[1] : "");
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new MyTestEnvironment(command_line));
    RUN_ALL_TESTS();
}

