#include "SimulatorType.h"
#include <cassert>

namespace Ers
{

    std::string SimulatorTypeName(SimulatorType type)
    {
        switch (type)
        {
            case SimulatorType::DiscreteEvent:
                return "Discrete-Event";
            case SimulatorType::AgentBased:
                return "Agent-Based";
            case SimulatorType::Continuous:
                return "Continuous";
            case SimulatorType::Emulation:
                return "Emulation";
            default:
                assert(false); // "SimulatorType doesn't exist"
                return "";
        }
    }

    SimulatorType SimulatorNameToType(const std::string_view& typeName)
    {
        if (typeName == "Discrete-Event")
        {
            return SimulatorType::DiscreteEvent;
        }
        else if (typeName == "Agent-Based")
        {
            return SimulatorType::AgentBased;
        }
        else if (typeName == "Continuous")
        {
            return SimulatorType::Continuous;
        }
        else if (typeName == "Emulation")
        {
            return SimulatorType::Emulation;
        }
        else
        {
            assert(false); // "SimulatorType doesn't exist"
            std::abort();
        }
    }

} // namespace Ers