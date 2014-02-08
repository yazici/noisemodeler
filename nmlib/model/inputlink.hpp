#ifndef NM_INPUTLINK_HPP
#define NM_INPUTLINK_HPP

#include <nmlib/util/userdataprovider.hpp>
#include <nmlib/util/signals.hpp>

namespace nm {

class Module;
class ModuleInput;
class OutputLink;

/**
 * @brief Describes which output of which node a ModuleInput of a specific Module is connected to.
 */
class InputLink : public UserDataProvider
{
public:
    explicit InputLink(const Module &owner, const ModuleInput &type):
        c_owner(owner),
        c_moduleInput(type),
        p_outputLink(nullptr)
    {}
    virtual ~InputLink();
    bool link(OutputLink &output);
    void unlink();
    const Module& getOwner() const {return c_owner;}
    const ModuleInput& getModuleInput() const {return c_moduleInput;}
    const OutputLink* getOutputLink() const {return p_outputLink;}
    OutputLink* getOutputLink() {return p_outputLink;}

    //signals
    signal<void (InputLink&)> linkChanged;
    signal<void (InputLink&)> destroying;

private:
    const Module& c_owner;
    const ModuleInput& c_moduleInput;
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP
