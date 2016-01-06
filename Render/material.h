#include "color.h"
#include "texture.h"

#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material();
    Material(Color ambient, Color diffuse, Color specular, double shininess=1.0,
             double ior=0.0, double reflect=0.0, double dissolve=1.0, double glossy=0.0);

    Color getAmbient();
    void setAmbient(Color value);

    Color getDiffuse();
    void setDiffuse(Color value);

    Color getSpecular();
    void setSpecular(Color value);

    double getShininess();
    void setShininess(double value);

    double getIor();
    void setIor(double value);

    double getReflect();
    void setReflect(double value);

    double getDissolve();
    void setDissolve(double value);

    double getGlossy();
    void setGlossy(double value);

private:
    Color k[3];
    double glossy;
    double shininess;
    double ior;
    double dissolve;
    double reflect;
};

#endif // MATERIAL_H
