#include "SubModelRandomProperties.h"

#include "Ers/Api.h"

namespace Ers
{
    void SubModelRandomProperties::SetRandomGenerator(Ers::RandomGeneratorType randomNumberGeneratorType)
    {
        Ers::Engine::ERS_SubModelRandomProperties_SetRandomGenerator_Type(CorePtr(), static_cast<int>(randomNumberGeneratorType));
    }

    void SubModelRandomProperties::SetRepetitive(bool value)
    {
        Ers::Engine::ERS_SubModelRandomProperties_SetRepetitive(CorePtr(), value);
    }

    void SubModelRandomProperties::SetAntithetical(bool value)
    {
        Ers::Engine::ERS_SubModelRandomProperties_SetAntithetical(CorePtr(), value);
    }

    void SubModelRandomProperties::SetSeed(size_t seed)
    {
        Ers::Engine::ERS_SubModelRandomProperties_SetSeed(CorePtr(), seed);
    }

    bool SubModelRandomProperties::IsRepetitive()
    {
        return Ers::Engine::ERS_SubModelRandomProperties_IsRepetitive(CorePtr());
    }

    bool SubModelRandomProperties::IsAntithetical()
    {
        return Ers::Engine::ERS_SubModelRandomProperties_IsAntithetical(CorePtr());
    }

    [[nodiscard]] size_t SubModelRandomProperties::GetOriginalSeed() const
    {
        return Ers::Engine::ERS_SubModelRandomProperties_GetOriginalSeed(CorePtr());
    }

    [[nodiscard]] Ers::RandomGenerator& SubModelRandomProperties::GetRandomNumberGenerator()
    {
        void* coreRandomGeneratorInstance = Ers::Engine::ERS_SubModelRandomProperties_GetRandomNumberGenerator(CorePtr());
        return *static_cast<Ers::RandomGenerator*>(coreRandomGeneratorInstance);
    }

    void* SubModelRandomProperties::CorePtr()
    {
        return this;
    }

    const void* const SubModelRandomProperties::CorePtr() const
    {
        return this;
    }
} // namespace Ers
