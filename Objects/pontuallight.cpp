#include "pontuallight.h"

PontualLight::PontualLight() : Light()
{
    this->type = "LIGHT_PONTUAL";
}

PontualLight::PontualLight(Material material, double intensity) : Light(material, intensity)
{
    this->type = "LIGHT_PONTUAL";
}
