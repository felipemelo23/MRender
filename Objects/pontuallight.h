#include "light.h"

#ifndef PONTUALLIGHT_H
#define PONTUALLIGHT_H

class PontualLight : public Light
{
public:
    PontualLight();
    PontualLight(Material material, double intensity=1);
};

#endif // PONTUALLIGHT_H
