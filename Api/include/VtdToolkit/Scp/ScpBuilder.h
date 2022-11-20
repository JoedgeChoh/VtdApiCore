#ifndef SCP_BUILDER_H
#define SCP_BUILDER_H

#include <string>
#include <sstream>
#include <stack>
#include <VtdCore/Macros.h>

namespace VTD {

class ScpAttributeBase
{
public:

    const ScpAttributeBase* getNext() const { return next_; }
    virtual void asString(std::ostream& ss) = 0;

protected:

    virtual ~ScpAttributeBase();
    ScpAttributeBase* getNext() { return next_; }

    friend class ScpBuilder;
    friend class ScpCommand;
    ScpAttributeBase* next_;

};

template<typename T>
class ScpAttribute : ScpAttributeBase
{

private:
    friend class ScpBuilder;

    ScpAttribute(const std::string& _name, const T& _value)
        : ScpAttributeBase()
        , name_(_name)
        , value_(_value) { }

    virtual void asString(std::ostream& stream) { asString<T>(*this, stream); }

    template<typename X>
    static void asString(const ScpAttribute<X>& attribute, std::ostream& stream)
    {
        stream << attribute.name_ << "=\"" << attribute.value_ << "\"";
    }

    std::string name_;
    T value_;

};

/**
 * @brief The ScpCommand class represents a single SCP command tag.
 * It holds pointers to its attributes and children and can be converted into
 * an SCP string.
 */
class ScpCommand {

public:
    // Root tags
    static const ScpCommand Player;
    static const ScpCommand Set;
    static const ScpCommand SimCtrl;
    static const ScpCommand Sensor;
    static const ScpCommand Symbol;
    static const ScpCommand Traffic;
    static const ScpCommand Query;

    // SimCtrl sub tags
    static const ScpCommand Apply;
    static const ScpCommand Config;
    static const ScpCommand Create;
    static const ScpCommand Delete;
    static const ScpCommand Init;
    static const ScpCommand InitDone;
    static const ScpCommand LoadScenario;
    static const ScpCommand Pause;
    static const ScpCommand PosInertial;
    static const ScpCommand PosRelative;
    static const ScpCommand PosRelativeRoad;
    static const ScpCommand Project;
    static const ScpCommand Restart;
    static const ScpCommand Speed;
    static const ScpCommand SpeedRelative;
    static const ScpCommand Start;
    static const ScpCommand Step;
    static const ScpCommand Stop;
    static const ScpCommand Sync;
    static const ScpCommand UnloadSensors;

    // Sensor sub tags
    static const ScpCommand Load;
    static const ScpCommand Frustum;
    static const ScpCommand Position;
    static const ScpCommand Origin;
    static const ScpCommand Cull;
    static const ScpCommand Port;
    static const ScpCommand Filter;
    static const ScpCommand Debug;

    // Screen text message
    static const ScpCommand Text;
    static const ScpCommand PosScreen;

    ScpCommand(const ScpCommand& other);
    ~ScpCommand();

    std::string asString() const;

    ScpAttributeBase* getFirstAttribute() const { return firstAttribute_; }
    ScpCommand* getFirstChild() const { return firstChild_; }
    ScpCommand* getNext() const { return next_; }

private:
    friend class ScpBuilder;

    ScpCommand(const char* tagName_);

    static void asString(const ScpCommand& cmd, std::stringstream& stream);

    std::string tagName_;
    ScpAttributeBase* firstAttribute_;
    ScpCommand* firstChild_;
    ScpCommand* next_;
};

/**
 * @brief The ScpBuilder class assists with the type and syntax safe creation of ScpCommands at runtime.
 *
 * Usage:
 *
 */
class ScpBuilder
{

public:

    ScpBuilder();
    ~ScpBuilder();

    /**
     * @brief Begin a new command tag, this will be the current ScpCommand.
     * Each BeginScpCommand call must have a closing EndScpCommand call.
     * Subsequent calls to BeginScpCommand before a closing EndScpCommand will create child tags.
     * @param command The scp command to open.
     */
    void beginScpCommand(const ScpCommand& command);

    /**
     * Add an attribute to the current ScpCommand.
     */
    template<typename T>
    void addScpAttribute(const std::string& name, const T& value)
    {
        VTD_ASSERT(currentScpCommand_ != 0);

        ScpAttributeBase* attribute = new ScpAttribute<T>(name, value);
        if (currentAttribute_ == 0)
        {
            currentAttribute_ = attribute;
            currentScpCommand_->firstAttribute_ = attribute;
        }
        else
        {
            currentAttribute_->next_ = attribute;
            currentAttribute_ = attribute;
        }
    }

    template<typename T>
    void addScpAttribute(const std::string& name, const T* value);

    /**
     * @brief End the current command tag.
     * After a call to EndScpCommand the current ScpCommand will be the parent or 0.
     */
    const ScpCommand& endScpCommand();

    /**
     * Get a string representation of all SCP commands created since the last asString call.
     * Clears commands from queue.
     * @return SCP string.
     */
    std::string asString();

private:
    void addChildCommand(ScpCommand& parent, ScpCommand& child);

    ScpCommand rootCommand_; // root node for all commands.

    ScpCommand* currentScpCommand_;
    ScpAttributeBase* currentAttribute_;
    std::stack<ScpCommand*> scpCommandHierarchy_;
};

} //namespace VTD

#endif //SCP_BUILDER_H
