#ifndef NM_MODULEOUTPUT_HPP
#define NM_MODULEOUTPUT_HPP

#include <nmlib/model/signaltype.hpp>
#include <nmlib/util/userdataprovider.hpp>

#include <nmlib/util/signals.hpp>

#include <string>

namespace nm {

class ModuleType;

/**
 * @brief Describes one of a ModuleType's outputs (name, SignalType)
 * @ingroup model
 */
class ModuleOutput : public UserDataProvider
{
public:
    explicit ModuleOutput(std::string name, SignalType signalType, const ModuleType&) :
        c_name(name),
        c_signalType(signalType)
    {}
    ~ModuleOutput(){destroying(*this);}
//    ModuleOutput(ModuleOutput&&) = default;
//    ModuleOutput(ModuleOutput&) = default;

    std::string getName() const {return c_name;}
    SignalType getSignalType() const {return c_signalType;}

    signal<void(ModuleOutput&)> destroying;

private:
    const std::string c_name;
    const SignalType c_signalType;
};

} // namespace nm

#endif // NM_MODULEOUTPUT_HPP
