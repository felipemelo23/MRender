#include "cone.h"

Cone::Cone() : Object3D()
{
    this->type = "OBJCONE";
}

Cone::Cone(Material material) : Object3D(material)
{
    this->type = "OBJCONE";
}

pair<Vec4, Vec4> Cone::checkIntersect(Ray raySend)
{
    Ray ray = raySend;
    ray.setOrigin(getCLTMatrixInvOrigin(raySend.getOrigin()));
    Vec4 dir = getCLTMatrixInvDir(raySend.getDirection());
    dir.normalize();
    ray.setDirection(dir);

    double a = pow(ray.getDirection().getX(),2) -
               pow(ray.getDirection().getY(),2) +
               pow(ray.getDirection().getZ(),2);
    double b = 2*(ray.getOrigin().getX()*ray.getDirection().getX() -
                  ray.getOrigin().getY()*ray.getDirection().getY() +
                  ray.getOrigin().getZ()*ray.getDirection().getZ());
    double c = pow(ray.getOrigin().getX(),2) -
               pow(ray.getOrigin().getY(),2) +
               pow(ray.getOrigin().getZ(),2) - 0;

    pair<Vec4, Vec4> base = checkBaseIntersect(ray);
    pair<Vec4, Vec4> fold = checkFoldIntersect(ray,a,b,c);

    return minResult(base,fold);
}

pair<Vec4, Vec4> Cone::minResult(pair<Vec4, Vec4> a, pair<Vec4, Vec4> b)
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

Vec4 Cone::getMin()
{
    Vec4 v[8];
    double xmin, ymin, zmin;
    xmin = ymin = zmin = INT_MAX;

    v[0] = getCLTMatrixOrigin(Vec4(1,0,1,1));
    v[1] = getCLTMatrixOrigin(Vec4(1,0,-1,1));
    v[2] = getCLTMatrixOrigin(Vec4(-1,0,1,1));
    v[3] = getCLTMatrixOrigin(Vec4(-1,0,-1,1));
    v[4] = getCLTMatrixOrigin(Vec4(1,-1,1,1));
    v[5] = getCLTMatrixOrigin(Vec4(1,-1,-1,1));
    v[6] = getCLTMatrixOrigin(Vec4(-1,-1,1,1));
    v[7] = getCLTMatrixOrigin(Vec4(-1,-1,-1,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() < xmin) xmin = v[i].getX();
        if (v[i].getY() < ymin) ymin = v[i].getY();
        if (v[i].getZ() < zmin) zmin = v[i].getZ();
    }

    return Vec4(xmin,ymin,zmin);
}

Vec4 Cone::getMax()
{
    Vec4 v[8];
    double xmax, ymax, zmax;
    xmax = ymax = zmax = INT_MIN;

    v[0] = getCLTMatrixOrigin(Vec4(1,0,1,1));
    v[1] = getCLTMatrixOrigin(Vec4(1,0,-1,1));
    v[2] = getCLTMatrixOrigin(Vec4(-1,0,1,1));
    v[3] = getCLTMatrixOrigin(Vec4(-1,0,-1,1));
    v[4] = getCLTMatrixOrigin(Vec4(1,-1,1,1));
    v[5] = getCLTMatrixOrigin(Vec4(1,-1,-1,1));
    v[6] = getCLTMatrixOrigin(Vec4(-1,-1,1,1));
    v[7] = getCLTMatrixOrigin(Vec4(-1,-1,-1,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() > xmax) xmax = v[i].getX();
        if (v[i].getY() > ymax) ymax = v[i].getY();
        if (v[i].getZ() > zmax) zmax = v[i].getZ();
    }

    return Vec4(xmax,ymax,zmax);
}

Color Cone::getTextureColor(Vec4 point)
{
    double v = 1 - (point.getY() + 1);
    double u;

    double ang = atan2(point.getZ(), point.getX());

    if (ang < 0) {
        u = -ang/(2*M_PI);
    } else {
        u = 1-ang/(2*M_PI);
    }

    return texture.getColorAt(u,v);
}

Vec4 Cone::getNormal(Vec4 point)
{
    if (isAlmost(point.getY(),1)) {
        return getCLTMatrixInvDir(Vec4(0,1,0)).normalize();
    } else if (isAlmost(point.getY(),-1)) {
        return getCLTMatrixInvDir(Vec4(0,-1,0)).normalize();
    } else {
        Vec4 normal = (Vec4(point.getX(),0,point.getZ()).normalize() + Vec4(0,baseRadius,0)).normalize();
        normal = getCLTMatrixInvDir(normal);
        normal.normalize();
        return normal;
    }
}

pair<Vec4,Vec4> Cone::checkBaseIntersect(Ray ray)
{
    if (ray.getDirection().getY() != 0) {
        double t = (-1 - ray.getOrigin().getY())/ray.getDirection().getY();
        if (t < 0) return make_pair(Vec4(),Vec4());
        Vec4 r = ray.findPoint(t);
        if (pow(r.getX(),2) + pow(r.getZ(),2) <= 1) return make_pair(Vec4(1,t,id),ray.findPoint(t));
        return make_pair(Vec4(),Vec4());
    }

    return make_pair(Vec4(),Vec4());
}

pair<Vec4,Vec4> Cone::checkFoldIntersect(Ray ray, double a, double b, double c)
{
    double delta = b*b - 4*a*c;

    if (delta < 0) return make_pair(Vec4(),Vec4());
    if (delta == 0) {
        return make_pair(Vec4(1,(-b/2*a),id),ray.findPoint(-b/2*a));
    }

    double t1 = (-b + sqrt(delta))/(2*a);
    double t2 = (-b - sqrt(delta))/(2*a);

    double t = qMin(t1,t2);

    if ((ray.findPoint(t).getY() < -1) || (ray.findPoint(t).getY() > 0)) return make_pair(Vec4(),Vec4());

    return make_pair(Vec4(1,t,id),ray.findPoint(t));
}
