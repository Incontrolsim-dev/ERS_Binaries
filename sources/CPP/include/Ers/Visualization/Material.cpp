#include "Material.h"
#include "Ers/Api.h"

namespace Ers
{
    Material::Material(void* corePointer) :
        data(corePointer)
    {
    }

    Ers::Color Material::GetColor() const
    {
        return Ers::Color::FromInt(Ers::Engine::ERS_Material_GetDiffuseColor(data));
    }

    void Material::SetColor(Ers::Color color)
    {
        Ers::Engine::ERS_Material_SetDiffuseColor(data, color.Value);
    }

    void* Material::CorePtr()
    {
        return data;
    }

    const void* const Material::CorePtr() const
    {
        return data;
    }
} // namespace Ers
