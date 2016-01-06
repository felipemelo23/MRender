#include "object3d.h"

#ifndef PLANE_H
#define PLANE_H

using namespace std;

class Plane : public Object3D
{
public:
    Plane();
    Plane(Material material);
    pair<Vec4,Vec4> checkIntersect(Ray raySend);
    Vec4 getMin();
    Vec4 getMax();
    Color getTextureColor(Vec4 point);
private:
    Vec4 getNormal(Vec4 point);
};

#endif // PLANE_H
