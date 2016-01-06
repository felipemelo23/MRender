#include "plane.h"

Plane::Plane() : Object3D() {
    this->type = "OBJPLANE";
}

Plane::Plane(Material material) : Object3D(material) {
    this->type = "OBJPLANE";
}

Vec4 Plane::getNormal(Vec4 point)
{
    Vec4 normal = getCLTMatrixInvDir(Vec4(0,0,1));
    normal.normalize();
    return normal;
}

pair<Vec4,Vec4> Plane::checkIntersect(Ray raySend)
{
    Ray ray = raySend;
    ray.setOrigin(getCLTMatrixInvOrigin(raySend.getOrigin()));
    ray.setDirection(getCLTMatrixInvDir(raySend.getDirection()));

    if(ray.getDirection().getZ() != 0) {
        double t = -ray.getOrigin().getZ()/ray.getDirection().getZ();
        double x = ray.findPoint(t).getX();
        double y = ray.findPoint(t).getY();

        if ((x<=0.5)&&(x>=-0.5)&&(y<=0.5)&&(y>=-0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    }
    return make_pair(Vec4(),Vec4());
}

Vec4 Plane::getMin()
{
    Vec4 v[4];
    double xmin, ymin, zmin;
    xmin = ymin = zmin = INT_MAX;

    v[0] = getCLTMatrixOrigin(Vec4(0.5,0.5,0,1));
    v[1] = getCLTMatrixOrigin(Vec4(0.5,-0.5,0,1));
    v[2] = getCLTMatrixOrigin(Vec4(-0.5,0.5,0,1));
    v[3] = getCLTMatrixOrigin(Vec4(-0.5,-0.5,0,1));

    for (unsigned int i = 0; i < 4; i++) {
        if (v[i].getX() < xmin) xmin = v[i].getX();
        if (v[i].getY() < ymin) ymin = v[i].getY();
        if (v[i].getZ() < zmin) zmin = v[i].getZ();
    }

    return Vec4(xmin,ymin,zmin);
}

Vec4 Plane::getMax()
{
    Vec4 v[4];
    double xmax, ymax, zmax;
    xmax = ymax = zmax = INT_MIN;

    v[0] = getCLTMatrixOrigin(Vec4(0.5,0.5,0,1));
    v[1] = getCLTMatrixOrigin(Vec4(0.5,-0.5,0,1));
    v[2] = getCLTMatrixOrigin(Vec4(-0.5,0.5,0,1));
    v[3] = getCLTMatrixOrigin(Vec4(-0.5,-0.5,0,1));

    for (unsigned int i = 0; i < 4; i++) {
        if (v[i].getX() > xmax) xmax = v[i].getX();
        if (v[i].getY() > ymax) ymax = v[i].getY();
        if (v[i].getZ() > zmax) zmax = v[i].getZ();
    }

    return Vec4(xmax,ymax,zmax);
}

//Point em coordenadas do objeto
Color Plane::getTextureColor(Vec4 point)
{
    return this->texture.getColorAt(0.5 + point.getX(), 0.5 - point.getY());
}
