#include "box.h"

Box::Box() : Object3D() {
    this->type = "OBJCUBE";
}

Box::Box(Material material) : Object3D(material) {
    this->type = "OBJCUBE";
}

Vec4 Box::getNormal(Vec4 point)
{
    Vec4 normal;

    if (isAlmost(point.getX(),-0.5)) {
        normal = getCLTMatrixInvDir(Vec4(-1,0,0));
        normal.normalize();
        return normal;
    }
    if (isAlmost(point.getX(),0.5)) {
        normal = getCLTMatrixInvDir(Vec4(1,0,0));
        normal.normalize();
        return normal;
    }
    if (isAlmost(point.getY(),-0.5)) {
        normal = getCLTMatrixInvDir(Vec4(0,-1,0));
        normal.normalize();
        return normal;
    }
    if (isAlmost(point.getY(),0.5)) {
        normal = getCLTMatrixInvDir(Vec4(0,1,0));
        normal.normalize();
        return normal;
    }
    if (isAlmost(point.getZ(),-0.5)) {
        normal = getCLTMatrixInvDir(Vec4(0,0,-1));
        normal.normalize();
        return normal;
    }
    if (isAlmost(point.getZ(),0.5)) {
        normal = getCLTMatrixInvDir(Vec4(0,0,1));
        normal.normalize();
        return normal;
    }
    return Vec4();
}

pair<Vec4,Vec4> Box::checkIntersect(Ray raySend)
{
    Ray ray = raySend;
    ray.setOrigin(getCLTMatrixInvOrigin(raySend.getOrigin()));
    ray.setDirection(getCLTMatrixInvDir(raySend.getDirection()));

    if (ray.getDirection().getX() < 0) {
        double t = (0.5 - ray.getOrigin().getX())/ray.getDirection().getX();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getY() >= -0.5)&&(pT.getY() <= 0.5)&&
            (pT.getZ() >= -0.5)&&(pT.getZ() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    } else if (ray.getDirection().getX() > 0){
        double t = (-0.5 - ray.getOrigin().getX())/ray.getDirection().getX();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getY() >= -0.5)&&(pT.getY() <= 0.5)&&
            (pT.getZ() >= -0.5)&&(pT.getZ() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    }

    if (ray.getDirection().getY() < 0) {
        double t = (0.5 - ray.getOrigin().getY())/ray.getDirection().getY();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getX() >= -0.5)&&(pT.getX() <= 0.5)&&
            (pT.getZ() >= -0.5)&&(pT.getZ() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    } else if (ray.getDirection().getY() > 0){
        double t = (-0.5 - ray.getOrigin().getY())/ray.getDirection().getY();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getX() >= -0.5)&&(pT.getX() <= 0.5)&&
            (pT.getZ() >= -0.5)&&(pT.getZ() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    }

    if (ray.getDirection().getZ() < 0) {
        double t = (0.5 - ray.getOrigin().getZ())/ray.getDirection().getZ();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getY() >= -0.5)&&(pT.getY() <= 0.5)&&
            (pT.getX() >= -0.5)&&(pT.getX() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    } else if (ray.getDirection().getZ() > 0){
        double t = (-0.5 - ray.getOrigin().getZ())/ray.getDirection().getZ();
        Vec4 pT = ray.findPoint(t);
        if ((pT.getY() >= -0.5)&&(pT.getY() <= 0.5)&&
            (pT.getX() >= -0.5)&&(pT.getX() <= 0.5)) {
            return make_pair(Vec4(1,t,id), ray.findPoint(t));
        }
    }

    return make_pair(Vec4(), Vec4());
}

Vec4 Box::getMin()
{
    Vec4 v[8];
    double xmin, ymin, zmin;
    xmin = ymin = zmin = INT_MAX;

    v[0] = getCLTMatrixOrigin(Vec4(halfSide,halfSide,halfSide,1));
    v[1] = getCLTMatrixOrigin(Vec4(halfSide,halfSide,-halfSide,1));
    v[2] = getCLTMatrixOrigin(Vec4(halfSide,-halfSide,halfSide,1));
    v[3] = getCLTMatrixOrigin(Vec4(halfSide,-halfSide,-halfSide,1));
    v[4] = getCLTMatrixOrigin(Vec4(-halfSide,halfSide,halfSide,1));
    v[5] = getCLTMatrixOrigin(Vec4(-halfSide,halfSide,-halfSide,1));
    v[6] = getCLTMatrixOrigin(Vec4(-halfSide,-halfSide,halfSide,1));
    v[7] = getCLTMatrixOrigin(Vec4(-halfSide,-halfSide,-halfSide,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() < xmin) xmin = v[i].getX();
        if (v[i].getY() < ymin) ymin = v[i].getY();
        if (v[i].getZ() < zmin) zmin = v[i].getZ();
    }

    return Vec4(xmin,ymin,zmin);
}

Vec4 Box::getMax()
{
    Vec4 v[8];
    double xmax, ymax, zmax;
    xmax = ymax = zmax = INT_MIN;

    v[0] = getCLTMatrixOrigin(Vec4(halfSide,halfSide,halfSide,1));
    v[1] = getCLTMatrixOrigin(Vec4(halfSide,halfSide,-halfSide,1));
    v[2] = getCLTMatrixOrigin(Vec4(halfSide,-halfSide,halfSide,1));
    v[3] = getCLTMatrixOrigin(Vec4(halfSide,-halfSide,-halfSide,1));
    v[4] = getCLTMatrixOrigin(Vec4(-halfSide,halfSide,halfSide,1));
    v[5] = getCLTMatrixOrigin(Vec4(-halfSide,halfSide,-halfSide,1));
    v[6] = getCLTMatrixOrigin(Vec4(-halfSide,-halfSide,halfSide,1));
    v[7] = getCLTMatrixOrigin(Vec4(-halfSide,-halfSide,-halfSide,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() > xmax) xmax = v[i].getX();
        if (v[i].getY() > ymax) ymax = v[i].getY();
        if (v[i].getZ() > zmax) zmax = v[i].getZ();
    }

    return Vec4(xmax,ymax,zmax);
}

Color Box::getTextureColor(Vec4 point)
{
    Color color = Color();
    if (isAlmost(point.getX(),-0.5)) {
        color = texture.getColorAt(0.5 + point.getZ(),0.5 - point.getY());
    }
    if (isAlmost(point.getX(),0.5)) {
        color = texture.getColorAt(0.5 + point.getZ(),0.5 - point.getY());
    }
    if (isAlmost(point.getY(),-0.5)) {
        color = texture.getColorAt(0.5 + point.getX(),0.5 - point.getZ());
    }
    if (isAlmost(point.getY(),0.5)) {
        color = texture.getColorAt(0.5 + point.getX(),0.5 - point.getZ());
    }
    if (isAlmost(point.getZ(),-0.5)) {
        color = texture.getColorAt(0.5 + point.getX(),0.5 - point.getY());
    }
    if (isAlmost(point.getZ(),0.5)) {
        color = texture.getColorAt(0.5 + point.getX(),0.5 - point.getY());
    }
    return color;
}
