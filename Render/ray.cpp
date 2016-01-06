#include "ray.h"

Ray::Ray()
{
    origin = Vec4();
    direction = Vec4(1,0,0);
}

Ray::Ray(Vec4 origin, Vec4 direction)
{
    this->origin = origin;
    this->direction = direction;
}

Vec4 Ray::getOrigin()
{
    return origin;
}

void Ray::setOrigin(Vec4 value)
{
    origin = value;
}
Vec4 Ray::getDirection()
{
    return direction;
}

void Ray::setDirection(Vec4 value)
{
    direction = value;
}

Vec4 Ray::findPoint(double t)
{
    return Vec4(origin.getX()+direction.getX()*t,
                origin.getY()+direction.getY()*t,
                origin.getZ()+direction.getZ()*t,1);
}


