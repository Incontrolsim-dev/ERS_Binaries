#include "Material.h"
#include "Ers/Api.h"

namespace Ers
{
    Material::Material(void* corePointer) :
        data(corePointer)
    {
    }

    Ers::Vector3 Material::Color() const
    {
        return Ers::Vec3(
            *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_X(data)),
            *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_Y(data)),
            *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_Z(data)));
    }

    void Material::Color(const Ers::Vector3& color)
    {
        *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_X(data)) = color.X;
        *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_Y(data)) = color.Y;
        *static_cast<float*>(ersAPIFunctionPointers.ERS_Material_Color_Z(data)) = color.Z;
    }

    void* Material::Data()
    {
        return data;
    }

    const void* const Material::Data() const
    {
        return data;
    }
} // namespace Ers
