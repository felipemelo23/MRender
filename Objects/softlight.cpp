#include "softlight.h"

SoftLight::SoftLight() : Light()
{
    this->type = "LIGHT_SOFT";
    this->size = 1.0;
}

SoftLight::SoftLight(double size)
{
    this->type = "LIGHT_SOFT";
    this->size = size;
}

SoftLight::SoftLight(Material material, double size, double intensity) : Light(material,intensity)
{
    this->type = "LIGHT_SOFT";
    this->size = size;
}

Vec4 SoftLight::getOrigin()
{
    cout << "Soft" << endl;
    return getCLTMatrix()*Vec4(fRand(-size,size),fRand(-size,size),fRand(-size,size),1);
}

double SoftLight::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


