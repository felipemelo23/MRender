#include "object3d.h"

#ifndef BOX_H
#define BOX_H

using namespace std;

class Box : public Object3D
{
public:
    Box();
    Box(Material material);
    pair<Vec4,Vec4> checkIntersect(Ray raySend);
    Vec4 getMin();
    Vec4 getMax();
    Color getTextureColor(Vec4 point);
private:
    double halfSide = 0.5;
    Vec4 getNormal(Vec4 point);
};

#endif // BOX_H
