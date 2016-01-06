#include "object3d.h"

#ifndef CONE_H
#define CONE_H

class Cone : public Object3D
{
public:
    Cone();
    Cone(Material material);
    pair<Vec4,Vec4> checkIntersect(Ray raySend);
    Vec4 getMin();
    Vec4 getMax();
    Color getTextureColor(Vec4 point);

private:
    double topRadius = 0.5;
    double baseRadius = 1;
    Vec4 getNormal(Vec4 point);
    pair<Vec4, Vec4> checkBaseIntersect(Ray ray);
    pair<Vec4, Vec4> checkFoldIntersect(Ray ray, double a, double b, double c);
    pair<Vec4, Vec4> minResult(pair<Vec4, Vec4> a, pair<Vec4, Vec4> b);
};

#endif // CONE_H
