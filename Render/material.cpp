#include "material.h"

Material::Material()
{
    k[0] = k[1] = k[2] = Color(1,1,1);
    shininess = 0;
    ior = 1.0;
    reflect = 0;
    dissolve = 1.0;
    glossy = 0;
}

Material::Material(Color ambient, Color diffuse, Color specular, double shininess, double ior, double reflect, double dissolve, double glossy)
{
    k[0] = ambient;
    k[1] = diffuse;
    k[2] = specular;
    this->shininess = shininess;
    this->ior = ior;
    this->reflect = reflect;
    this->dissolve = dissolve;
    this->glossy = glossy;
}

Color Material::getAmbient()
{
    return k[0];
}

void Material::setAmbient(Color value)
{
    k[0] = value;
}

Color Material::getDiffuse()
{
    return k[1];
}

void Material::setDiffuse(Color value)
{
    k[1] = value;
}

Color Material::getSpecular()
{
    return k[2];
}

void Material::setSpecular(Color value)
{
    k[2] = value;
}

double Material::getShininess()
{
    return shininess;
}

void Material::setShininess(double value)
{
    shininess = value;
}
double Material::getIor()
{
    return ior;
}

void Material::setIor(double value)
{
    ior = value;
}
double Material::getReflect()
{
    return reflect;
}

void Material::setReflect(double value)
{
    reflect = value;
}
double Material::getDissolve()
{
    return dissolve;
}

void Material::setDissolve(double value)
{
    dissolve = value;
}
double Material::getGlossy()
{
    return glossy;
}

void Material::setGlossy(double value)
{
    glossy = value;
}





