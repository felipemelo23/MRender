#include "box.h"
#include "cylinder.h"

Cylinder::Cylinder() : Object3D() {
    this->type = "OBJCYLINDER";
}

Cylinder::Cylinder(Material material) : Object3D(material) {
    this->type = "OBJCYLINDER";
}

Vec4 Cylinder::getNormal(Vec4 point)
{
    if (isAlmost(point.getY(),1)) {
        return getCLTMatrixInvDir(Vec4(0,1,0)).normalize();
    } else if (isAlmost(point.getY(),-1)) {
        return getCLTMatrixInvDir(Vec4(0,-1,0)).normalize();
    } else {
        Vec4 normal = Vec4(point.getX(),0,point.getZ());
        normal = getCLTMatrixInvDir(normal);
        normal.normalize();
        return normal;
    }
}

pair<Vec4, Vec4> Cylinder::minResult(pair<Vec4, Vec4> a, pair<Vec4, Vec4> b)
{
    if ((a.first.getX() != 0) && b.first.getX() != 0) {
        if (a.first.getY() < b.first.getY())
            return a;
        return b;
    } else if (a.first.getX() != 0) {
        return a;
    } else {
        return b;
    }
}

pair<Vec4,Vec4> Cylinder::checkIntersect(Ray raySend)
{
    Ray ray = raySend;
    ray.setOrigin(getCLTMatrixInvOrigin(raySend.getOrigin()));
    ray.setDirection(getCLTMatrixInvDir(raySend.getDirection()));

    double a = pow(ray.getDirection().getX(),2) +
               pow(ray.getDirection().getZ(),2);
    double b = 2*(ray.getOrigin().getX()*ray.getDirection().getX() +
                  ray.getOrigin().getZ()*ray.getDirection().getZ());
    double c = pow(ray.getOrigin().getX(),2) +
               pow(ray.getOrigin().getZ(),2) - 1;

    double delta = b*b - 4*a*c;

    if (delta < 0) return make_pair(Vec4(), Vec4());

    pair<Vec4,Vec4> top = checkTopIntersect(ray);
    pair<Vec4,Vec4> base = checkBaseIntersect(ray);
    pair<Vec4,Vec4> fold = checkFoldIntersect(ray,a,b,c);

    return minResult(minResult(top,base),fold);
}



Vec4 Cylinder::getMin()
{
    Vec4 v[8];
    double xmin, ymin, zmin;
    xmin = ymin = zmin = INT_MAX;

    v[0] = getCLTMatrixOrigin(Vec4(1.5,1.5,1.5,1));
    v[1] = getCLTMatrixOrigin(Vec4(1.5,-0.5,1.5,1));
    v[2] = getCLTMatrixOrigin(Vec4(-1.5,1.5,1.5,1));
    v[3] = getCLTMatrixOrigin(Vec4(-1.5,-0.5,1.5,1));
    v[4] = getCLTMatrixOrigin(Vec4(-1.5,1.5,-1.5,1));
    v[5] = getCLTMatrixOrigin(Vec4(-1.5,-0.5,-1.5,1));
    v[6] = getCLTMatrixOrigin(Vec4(1.5,1.5,-1.5,1));
    v[7] = getCLTMatrixOrigin(Vec4(1.5,-0.5,1.5,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() < xmin) xmin = v[i].getX();
        if (v[i].getY() < ymin) ymin = v[i].getY();
        if (v[i].getZ() < zmin) zmin = v[i].getZ();
    }

    return Vec4(xmin,ymin,zmin);
}

Vec4 Cylinder::getMax()
{
    Vec4 v[8];
    double xmax, ymax, zmax;
    xmax = ymax = zmax = INT_MIN;

    v[0] = getCLTMatrixOrigin(Vec4(1.5,1.5,1.5,1));
    v[1] = getCLTMatrixOrigin(Vec4(1.5,-0.5,1.5,1));
    v[2] = getCLTMatrixOrigin(Vec4(-1.5,1.5,1.5,1));
    v[3] = getCLTMatrixOrigin(Vec4(-1.5,-0.5,1.5,1));
    v[4] = getCLTMatrixOrigin(Vec4(-1.5,1.5,-1.5,1));
    v[5] = getCLTMatrixOrigin(Vec4(-1.5,-0.5,-1.5,1));
    v[6] = getCLTMatrixOrigin(Vec4(1.5,1.5,-1.5,1));
    v[7] = getCLTMatrixOrigin(Vec4(1.5,-0.5,1.5,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() > xmax) xmax = v[i].getX();
        if (v[i].getY() > ymax) ymax = v[i].getY();
        if (v[i].getZ() > zmax) zmax = v[i].getZ();
    }

    return Vec4(xmax,ymax,zmax);
}

Color Cylinder::getTextureColor(Vec4 point)
{
    double v = 1 - (point.getY() + 1)/2;
    double u;

    double ang = atan2(point.getZ(), point.getX());

    if (ang < 0) {
        u = -ang/(2*M_PI);
    } else {
        u = 1-ang/(2*M_PI);
    }

    return texture.getColorAt(u,v);
}

pair<Vec4,Vec4> Cylinder::checkBaseIntersect(Ray ray)
{
    if (ray.getDirection().getY() != 0) {
        double t = (0 - ray.getOrigin().getY())/ray.getDirection().getY();
        if (t < 0) return make_pair(Vec4(),Vec4());
        Vec4 r = ray.findPoint(t);
        if (pow(r.getX(),2) + pow(r.getZ(),2) <= 1) return make_pair(Vec4(1,t,id),ray.findPoint(t));
        return make_pair(Vec4(),Vec4());
    }

    return make_pair(Vec4(),Vec4());
}

pair<Vec4,Vec4> Cylinder::checkTopIntersect(Ray ray)
{
    if (ray.getDirection().getY() != 0) {
        double t = (1 - ray.getOrigin().getY())/ray.getDirection().getY();
        if (t < 0) return make_pair(Vec4(),Vec4());

        Vec4 r = ray.findPoint(t);
        if (pow(r.getX(),2) + pow(r.getZ(),2) <= 1) return make_pair(Vec4(1,t,id),ray.findPoint(t));
        return make_pair(Vec4(),Vec4());
    }
    return make_pair(Vec4(),Vec4());
}

pair<Vec4,Vec4> Cylinder::checkFoldIntersect(Ray ray, double a, double b, double c)
{
    double delta = b*b - 4*a*c;
    double t1 = (-b + sqrt(delta))/(2*a);
    double t2 = (-b - sqrt(delta))/(2*a);

    if (t1 < 0) t1 = INT_MAX;
    if (t2 < 0) t2 = INT_MAX;

    double t = qMin<double>(t1,t2);

    Vec4 point = ray.findPoint(t);

    if ((point.getY() < 1) && (point.getY() > 0)) {
        return make_pair(Vec4(1,t,id),point);
    }
    return make_pair(Vec4(),Vec4());
}

