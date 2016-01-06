#include "light.h"

Light::Light() : Object3D()
{
    intensity = 1;
    type = "LIGHT_AMBIENT";
}

Light::Light(Material material, double intensity) : Object3D(material)
{
    this->intensity = intensity;
    type = "LIGHT_AMBIENT";
}

double Light::getIntensity() const
{
    return intensity;
}

void Light::setIntensity(double value)
{
    intensity = value;
}

Vec4 Light::getRandOrigin(){}


