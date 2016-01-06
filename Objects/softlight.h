#include "light.h"

#ifndef SOFTLIGHT_H
#define SOFTLIGHT_H

class SoftLight : public Light
{
public:
    SoftLight();
    SoftLight(double size);
    SoftLight(Material material, double size, double intensity=1);

    Vec4 getOrigin();

private:
    double size;
    double fRand(double fMin, double fMax);
};

#endif // SOFTLIGHT_H
