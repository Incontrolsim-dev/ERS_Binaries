#pragma once

#include <cstdint>
#include <string>

namespace Ers
{
    enum class SimulatorType
    {
        Unknown       = 99,
        DiscreteEvent = 0,
        AgentBased    = 1,
        Continuous    = 2,
        Emulation     = 3
    };

    std::string SimulatorTypeName(SimulatorType type);
    SimulatorType SimulatorNameToType(const std::string_view& typeName);
} // namespace Ers
