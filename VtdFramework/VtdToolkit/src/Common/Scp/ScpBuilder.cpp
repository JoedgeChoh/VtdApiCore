#include <VtdToolkit/Scp/ScpBuilder.h>

#include <sstream>

namespace VTD {

// Root tags
const ScpCommand ScpCommand::SimCtrl = ScpCommand("SimCtrl");
const ScpCommand ScpCommand::Player = ScpCommand("Player");
const ScpCommand ScpCommand::Set = ScpCommand("Set");
const ScpCommand ScpCommand::Sensor = ScpCommand("Sensor");
const ScpCommand ScpCommand::Symbol = ScpCommand("Symbol");
const ScpCommand ScpCommand::Traffic = ScpCommand("Traffic");
const ScpCommand ScpCommand::Query = ScpCommand("Query");

// Sub tags
const ScpCommand ScpCommand::Apply = ScpCommand("Apply");
const ScpCommand ScpCommand::Config = ScpCommand("Config");
const ScpCommand ScpCommand::Create = ScpCommand("Create");
const ScpCommand ScpCommand::Delete = ScpCommand("Delete");
const ScpCommand ScpCommand::Init = ScpCommand("Init");
const ScpCommand ScpCommand::InitDone = ScpCommand("InitDone");
const ScpCommand ScpCommand::LoadScenario = ScpCommand("LoadScenario");
const ScpCommand ScpCommand::Pause = ScpCommand("Pause");
const ScpCommand ScpCommand::PosInertial = ScpCommand("PosInertial");
const ScpCommand ScpCommand::PosRelative = ScpCommand("PosRelative");
const ScpCommand ScpCommand::PosRelativeRoad = ScpCommand("PosRelativeRoad");
const ScpCommand ScpCommand::Project = ScpCommand("Project");
const ScpCommand ScpCommand::Restart = ScpCommand("Restart");
const ScpCommand ScpCommand::Speed = ScpCommand("Speed");
const ScpCommand ScpCommand::SpeedRelative = ScpCommand("SpeedRelative");
const ScpCommand ScpCommand::Start = ScpCommand("Start");
const ScpCommand ScpCommand::Step = ScpCommand("Step");
const ScpCommand ScpCommand::Stop = ScpCommand("Stop");
const ScpCommand ScpCommand::Sync = ScpCommand("Sync");
const ScpCommand ScpCommand::UnloadSensors = ScpCommand("UnloadSensors");

// Sensor tags
const ScpCommand ScpCommand::Load = ScpCommand("Load");
const ScpCommand ScpCommand::Frustum = ScpCommand("Frustum");
const ScpCommand ScpCommand::Position = ScpCommand("Position");
const ScpCommand ScpCommand::Origin = ScpCommand("Origin");
const ScpCommand ScpCommand::Cull = ScpCommand("Cull");
const ScpCommand ScpCommand::Port = ScpCommand("Port");
const ScpCommand ScpCommand::Filter = ScpCommand("Filter");
const ScpCommand ScpCommand::Debug = ScpCommand("Debug");

// Screen text message
const ScpCommand ScpCommand::Text = ScpCommand("Text");
const ScpCommand ScpCommand::PosScreen = ScpCommand("PosScreen");

ScpAttributeBase::~ScpAttributeBase() {
    delete next_;
    next_ = 0;
}

ScpCommand::ScpCommand(const ScpCommand& other)
    : tagName_(other.tagName_)
    , firstAttribute_(other.firstAttribute_)
    , firstChild_(other.firstChild_)
    , next_(other.next_)
{
//
}

ScpCommand::~ScpCommand()
{
    delete firstAttribute_;
    firstAttribute_ = 0;
    delete firstChild_;
    firstChild_ = 0;
    delete next_;
    next_ = 0;
}

ScpCommand::ScpCommand(const char* _tagName)
    : tagName_(_tagName)
    , firstAttribute_(0)
    , firstChild_(0)
    , next_(0)
{
//
}

std::string ScpCommand::asString() const
{
    std::stringstream stream;
    asString(*this, stream);
    return stream.str();
}

void ScpCommand::asString(const ScpCommand& cmd, std::stringstream& stream)
{
    stream << "<" << cmd.tagName_;

    //add attributes
    ScpAttributeBase* attribute = cmd.getFirstAttribute();
    while (attribute != 0) {
        stream << " ";
        attribute->asString(stream);
        attribute = attribute->getNext();
    }

    ScpCommand* subCmd = cmd.getFirstChild();

    if(subCmd == 0)
    {
        stream << "/>";
    }
    else
    {
        stream << ">";

        ScpCommand* subCmd = cmd.getFirstChild();
        while (subCmd != 0)
        {
            asString(*subCmd, stream);
            subCmd = subCmd->getNext();
        }

        stream << "</" << cmd.tagName_ << ">";
    }
}

ScpBuilder::ScpBuilder()
    : rootCommand_("ROOT")
    , currentScpCommand_(0)
    , currentAttribute_(0)
{ }

ScpBuilder::~ScpBuilder()
{ }

void ScpBuilder::beginScpCommand(const ScpCommand& command)
{
    if (currentScpCommand_ == 0)
    {
        currentScpCommand_ = new ScpCommand(command);

        // Find the last command that was created (preserves order!)
        ScpCommand* lastCommand = rootCommand_.firstChild_;
        if (lastCommand)
        {
            while (lastCommand->next_ != 0)
            {
                lastCommand = lastCommand->next_;
            }
            lastCommand->next_ = currentScpCommand_;
        }
        else
        {
            rootCommand_.firstChild_ = currentScpCommand_;
        }
    }
    else
    {
        ScpCommand* newCommand = new ScpCommand(command);
        addChildCommand(*currentScpCommand_, *newCommand);
        scpCommandHierarchy_.push(currentScpCommand_);
        currentScpCommand_ = newCommand;
        currentAttribute_ = 0;
    }
}

const ScpCommand& ScpBuilder::endScpCommand()
{
    VTD_ASSERT(currentScpCommand_ != 0);

    ScpCommand* result = currentScpCommand_;
    if (!scpCommandHierarchy_.empty())
    { // switch to the parent ScpCommand.
        currentScpCommand_ = scpCommandHierarchy_.top();
        scpCommandHierarchy_.pop();

        ScpAttributeBase* currentAttribute = currentScpCommand_->firstAttribute_;
        if (currentAttribute)
        {
            while (currentAttribute->next_ != 0)
            {
                currentAttribute = currentAttribute->next_;
            }
        }
        currentAttribute_ = currentAttribute;
    }
    else
    {  //already at top level, set to 0
        currentScpCommand_ = 0;
        currentAttribute_ = 0;
    }
    return *result;
}

std::string ScpBuilder::asString()
{
    std::stringstream stream;
    ScpCommand* nextCmd = rootCommand_.firstChild_;
    while(nextCmd != 0)
    {
        ScpCommand::asString(*nextCmd, stream);
        nextCmd = nextCmd->next_;
    }
    delete rootCommand_.firstChild_;
    rootCommand_.firstChild_ = 0;
    return stream.str();
}

void ScpBuilder::addChildCommand(ScpCommand& parent, ScpCommand& child)
{
    if (parent.firstChild_ == 0)
    {
        parent.firstChild_ = &child;
    }
    else
    {
        ScpCommand* nextChild = parent.firstChild_;
        while (nextChild->next_ != 0)
        {
            nextChild = nextChild->next_;
        }
        nextChild->next_ = &child;
    }
}

template<>
void ScpBuilder::addScpAttribute(const std::string& name, const char* value)
{
    addScpAttribute<std::string>(name, std::string(value));
}

} //namespace VTD
