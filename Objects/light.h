#include "object3d.h"

#ifndef LIGHT_H
#define LIGHT_H

class Light : public Object3D
{
public:
    Light();
    Light(Material material, double intensity=1);

    double getIntensity() const;
    void setIntensity(double value);

    virtual Vec4 getRandOrigin();

private:
    double intensity;

};

#endif // LIGHT_H
