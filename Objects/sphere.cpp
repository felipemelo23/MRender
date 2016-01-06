#include "sphere.h"

Sphere::Sphere() : Object3D() {
    this->type = "OBJSPHERE";
}

Sphere::Sphere(Material material) : Object3D(material) {
    this->type = "OBJSPHERE";
}

Vec4 Sphere::getNormal(Vec4 point)
{
    Vec4 normal = Vec4(point.getX(),point.getY(),point.getZ());
    normal = getCLTMatrixInvDir(normal);
    normal.normalize();
    return normal;
}

pair<Vec4,Vec4> Sphere::checkIntersect(Ray raySend)
{
    Ray ray = raySend;
    ray.setOrigin(getCLTMatrixInvOrigin(raySend.getOrigin()));
    Vec4 dir = getCLTMatrixInvDir(raySend.getDirection());
    dir.normalize();
    ray.setDirection(dir);

    double a = pow(ray.getDirection().getX(),2) +
               pow(ray.getDirection().getY(),2) +
               pow(ray.getDirection().getZ(),2);
    double b = 2*(ray.getOrigin().getX()*ray.getDirection().getX() +
                  ray.getOrigin().getY()*ray.getDirection().getY() +
                  ray.getOrigin().getZ()*ray.getDirection().getZ());
    double c = pow(ray.getOrigin().getX(),2) +
               pow(ray.getOrigin().getY(),2) +
               pow(ray.getOrigin().getZ(),2) - radius;

    double delta = b*b - 4*a*c;

    if (delta < 0) return make_pair(Vec4(),Vec4());
    if (delta == 0) {
        return make_pair(Vec4(1,(-b/2*a),id),ray.findPoint(-b/2*a));
    }

    double t1 = (-b + sqrt(delta))/(2*a);
    double t2 = (-b - sqrt(delta))/(2*a);

    if (t1 < t2) {
        return make_pair(Vec4(1,t1,id),ray.findPoint(t1));
    }
    return make_pair(Vec4(1,t2,id),ray.findPoint(t2));
}



Vec4 Sphere::getMin()
{
    Vec4 v[8];
    double xmin, ymin, zmin;
    xmin = ymin = zmin = INT_MAX;

    v[0] = getCLTMatrixOrigin(Vec4(radius,radius,radius,1));
    v[1] = getCLTMatrixOrigin(Vec4(radius,radius,-radius,1));
    v[2] = getCLTMatrixOrigin(Vec4(radius,-radius,radius,1));
    v[3] = getCLTMatrixOrigin(Vec4(radius,-radius,-radius,1));
    v[4] = getCLTMatrixOrigin(Vec4(-radius,radius,radius,1));
    v[5] = getCLTMatrixOrigin(Vec4(-radius,radius,-radius,1));
    v[6] = getCLTMatrixOrigin(Vec4(-radius,-radius,radius,1));
    v[7] = getCLTMatrixOrigin(Vec4(-radius,-radius,-radius,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() < xmin) xmin = v[i].getX();
        if (v[i].getY() < ymin) ymin = v[i].getY();
        if (v[i].getZ() < zmin) zmin = v[i].getZ();
    }

    return Vec4(xmin,ymin,zmin);
}

Vec4 Sphere::getMax()
{
    Vec4 v[8];
    double xmax, ymax, zmax;
    xmax = ymax = zmax = INT_MIN;

    v[0] = getCLTMatrixOrigin(Vec4(radius,radius,radius,1));
    v[1] = getCLTMatrixOrigin(Vec4(radius,radius,-radius,1));
    v[2] = getCLTMatrixOrigin(Vec4(radius,-radius,radius,1));
    v[3] = getCLTMatrixOrigin(Vec4(radius,-radius,-radius,1));
    v[4] = getCLTMatrixOrigin(Vec4(-radius,radius,radius,1));
    v[5] = getCLTMatrixOrigin(Vec4(-radius,radius,-radius,1));
    v[6] = getCLTMatrixOrigin(Vec4(-radius,-radius,radius,1));
    v[7] = getCLTMatrixOrigin(Vec4(-radius,-radius,-radius,1));

    for (unsigned int i = 0; i < 8; i++) {
        if (v[i].getX() > xmax) xmax = v[i].getX();
        if (v[i].getY() > ymax) ymax = v[i].getY();
        if (v[i].getZ() > zmax) zmax = v[i].getZ();
    }

    return Vec4(xmax,ymax,zmax);
}

Color Sphere::getTextureColor(Vec4 point)
{
    double v = 0.5 - asin(point.getY())/M_PI;
    double u;

    double ang = atan2(point.getZ(), point.getX());

    if (ang < 0) {
        u = -ang/(2*M_PI);
    } else {
        u = 1-ang/(2*M_PI);
    }

    return texture.getColorAt(u,v);
}
