#include "inputlink.hpp"

#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/signaltype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

bool InputLink::link(OutputLink *output)
{
    if(output == nullptr || output == p_outputLink || p_type->p_type == output->p_type->p_type){
        return false;
    }
    if(p_outputLink != nullptr){
        unlink();
    }
    p_outputLink = output;
    output->addLink(this);
    return true;
}

void InputLink::unlink()
{
    if(p_outputLink == nullptr){
        return;
    }

    OutputLink *tmp = p_outputLink;
    p_outputLink = nullptr;
    if(tmp != nullptr){
        tmp->unlink(this);
    }
}

} // namespace nm