#include "object3d.h"

#ifndef CYLINDER_H
#define CYLINDER_H

using namespace std;

class Cylinder : public Object3D
{
public:
    Cylinder();
    Cylinder(Material material);
    pair<Vec4,Vec4> checkIntersect(Ray raySend);
    Vec4 getMin();
    Vec4 getMax();
    Color getTextureColor(Vec4 point);

private:
    pair<Vec4, Vec4> checkBaseIntersect(Ray ray);
    pair<Vec4, Vec4> checkTopIntersect(Ray ray);
    pair<Vec4, Vec4> checkFoldIntersect(Ray ray, double a, double b, double c);
    Vec4 getNormal(Vec4 point);
    pair<Vec4, Vec4> minResult(pair<Vec4, Vec4> a, pair<Vec4, Vec4> b);
};

#endif // CYLINDER_H
