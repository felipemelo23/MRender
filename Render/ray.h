#include <Math/vec4.h>

#ifndef RAY_H
#define RAY_H

class Ray
{
public:
    Ray();
    Ray(Vec4 origin, Vec4 direction);

    Vec4 getOrigin();
    void setOrigin(Vec4 value);

    Vec4 getDirection();
    void setDirection(Vec4 value);

    Vec4 findPoint(double t);

private:
    Vec4 origin;
    Vec4 direction;
};

#endif // RAY_H
