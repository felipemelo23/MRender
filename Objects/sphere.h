#include "object3d.h"
#include <cmath>

#ifndef SPHERE_H
#define SPHERE_H

using namespace std;

class Sphere : public Object3D
{
public:
    Sphere();
    Sphere(Material material);
    pair<Vec4,Vec4> checkIntersect(Ray raySend);
    Vec4 getMin();
    Vec4 getMax();
    Color getTextureColor(Vec4 point);
private:
    double radius = 1;
    Vec4 getNormal(Vec4 point);
};

#endif // SPHERE_H
