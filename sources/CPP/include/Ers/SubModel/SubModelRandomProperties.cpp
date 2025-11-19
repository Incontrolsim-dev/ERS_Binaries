#include "SubModelRandomProperties.h"

#include "Ers/Api.h"

namespace Ers
{
    void SubModelRandomProperties::SetRandomGenerator(Ers::RandomGeneratorType randomNumberGeneratorType)
    {
        ersAPIFunctionPointers.ERS_SubModelRandomProperties_SetRandomGenerator_Type(Data(), static_cast<int>(randomNumberGeneratorType));
    }

    void SubModelRandomProperties::SetRepetitive(bool value)
    {
        ersAPIFunctionPointers.ERS_SubModelRandomProperties_SetRepetitive(Data(), value);
    }

    void SubModelRandomProperties::SetAntithetical(bool value)
    {
        ersAPIFunctionPointers.ERS_SubModelRandomProperties_SetAntithetical(Data(), value);
    }

    void SubModelRandomProperties::SetSeed(size_t seed)
    {
        ersAPIFunctionPointers.ERS_SubModelRandomProperties_SetSeed(Data(), seed);
    }

    bool SubModelRandomProperties::IsRepetitive()
    {
        return ersAPIFunctionPointers.ERS_SubModelRandomProperties_IsRepetitive(Data());
    }

    bool SubModelRandomProperties::IsAntithetical()
    {
        return ersAPIFunctionPointers.ERS_SubModelRandomProperties_IsAntithetical(Data());
    }

    [[nodiscard]] size_t SubModelRandomProperties::GetOriginalSeed() const
    {
        return ersAPIFunctionPointers.ERS_SubModelRandomProperties_GetOriginalSeed(Data());
    }

    [[nodiscard]] Ers::RandomGenerator& SubModelRandomProperties::GetRandomNumberGenerator()
    {
        void* coreRandomGeneratorInstance = ersAPIFunctionPointers.ERS_SubModelRandomProperties_GetRandomNumberGenerator(Data());
        return *static_cast<Ers::RandomGenerator*>(coreRandomGeneratorInstance);
    }
    void* SubModelRandomProperties::Data()
    {
        return this;
    }

    const void* const SubModelRandomProperties::Data() const
    {
        return this;
    }
} // namespace Ers
