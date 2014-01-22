#ifndef NM_INPUTLINK_HPP
#define NM_INPUTLINK_HPP

namespace nm {

class Module;
class ModuleInput;
class OutputLink;

/**
 * @brief Describes which output of which node a ModuleInput of a specific Module is connected to.
 */
class InputLink
{
public:
    InputLink(Module *owner, const ModuleInput *type):p_owner(owner), p_type(type), p_outputLink(nullptr){}
    bool link(OutputLink *output);
    void unlink();

    const ModuleInput* const p_type;
    Module* const p_owner;
private:
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP