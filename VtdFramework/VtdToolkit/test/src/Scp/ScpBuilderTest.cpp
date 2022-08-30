#include <gtest/gtest.h>
#include <VtdToolkit/Scp/ScpBuilder.h>

using namespace VTD;

TEST(ScpBuilderTest, commandTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
    sb.endScpCommand();

    std::string cmdStr = sb.asString();
    EXPECT_STREQ(cmdStr.c_str(), "<SimCtrl/>");
}

TEST(ScpBuilderTest, subCommandTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.beginScpCommand(ScpCommand::Start);
        sb.endScpCommand();
    sb.endScpCommand();

    std::string cmdStr = sb.asString();
    EXPECT_STREQ(cmdStr.c_str(), "<SimCtrl><Start/></SimCtrl>");
}

TEST(ScpBuilderTest, multiCommandTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.beginScpCommand(ScpCommand::Start);
        sb.endScpCommand();
    sb.endScpCommand();

    sb.beginScpCommand(ScpCommand::SimCtrl);
    sb.endScpCommand();

    std::string cmdStr = sb.asString();
    EXPECT_STREQ(cmdStr.c_str(), "<SimCtrl><Start/></SimCtrl><SimCtrl/>");
}

TEST(ScpBuilderTest, attributeTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.beginScpCommand(ScpCommand::Start);
        sb.addScpAttribute("tMax", 10.0f);
        sb.endScpCommand();
    sb.endScpCommand();

    std::string cmdStr = sb.asString();
    EXPECT_STREQ(cmdStr.c_str(), "<SimCtrl><Start tMax=\"10\"/></SimCtrl>");
}

TEST(ScpBuilderTest, attributeTest2)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.beginScpCommand(ScpCommand::Start);
        sb.addScpAttribute("tMax", 10.0f);
        sb.addScpAttribute("tMin", 0.1f);
        sb.endScpCommand();
    sb.endScpCommand();

    std::string cmdString = sb.asString();
    EXPECT_STREQ(cmdString.c_str(), "<SimCtrl><Start tMax=\"10\" tMin=\"0.1\"/></SimCtrl>");
}

TEST(ScpBuilderTest, attributeTest3)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.addScpAttribute("abc", 1);
        sb.addScpAttribute("def", 2.1f);
        sb.addScpAttribute("ghj", "3.0");
    sb.endScpCommand();

    std::string cmdString = sb.asString();
    EXPECT_STREQ(cmdString.c_str(), "<SimCtrl abc=\"1\" def=\"2.1\" ghj=\"3.0\"/>");
}

TEST(ScpBuilderTest, subCommandAttributesTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::Player); // TODO [BB] create player root command in shared method
    sb.addScpAttribute("name", std::string("playerName"));
        sb.beginScpCommand(ScpCommand::Create);
        sb.addScpAttribute("category", std::string("vehicle"));
        sb.endScpCommand();
    sb.endScpCommand();

    std::string cmdString = sb.asString();
    EXPECT_STREQ(cmdString.c_str(), "<Player name=\"playerName\"><Create category=\"vehicle\"/></Player>");
}


TEST(ScpBuilderTest, loadScenarioTest)
{
    ScpBuilder sb;
    sb.beginScpCommand(ScpCommand::SimCtrl);
        sb.beginScpCommand(ScpCommand::LoadScenario);
        sb.addScpAttribute("filename", std::string("test.xml"));
        sb.endScpCommand();
    sb.endScpCommand();

    std::string cmdString = sb.asString();
    EXPECT_STREQ(cmdString.c_str(), "<SimCtrl><LoadScenario filename=\"test.xml\"/></SimCtrl>");
 }



