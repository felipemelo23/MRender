#include "vec4.h"

Vec4::Vec4() {
    x = y = z = 0;
    w = 1;
}

Vec4::Vec4(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
double Vec4::getX() const {
    return x;
}

void Vec4::setX(double value) {
    x = value;
}
double Vec4::getY() const {
    return y;
}

void Vec4::setY(double value) {
    y = value;
}

double Vec4::getZ() const {
    return z;
}

void Vec4::setZ(double value) {
    z = value;
}

double Vec4::getMode() const {
    return w;
}

void Vec4::setMode(double value) {
    w = value;
}

Vec4 Vec4::normalize() {
    double norm = calculateNorm();
    x = x/norm;
    y = y/norm;
    z = z/norm;
    return Vec4(x,y,z);
}

double Vec4::calculateNorm() {
    return sqrt(pow(x,2)+pow(y,2)+pow(z,2));
}

void Vec4::print()
{
    cout << "[" << x << " " << y << " " << z << " " << w << "]" << endl;
}

void Vec4::removeNoise()
{
    if (fabs(x) <= PRECISION) {x = 0;}
    if (fabs(y) <= PRECISION) {y = 0;}
    if (fabs(z) <= PRECISION) {z = 0;}
    if (fabs(w) <= PRECISION) {w = 0;}
}

Vec4 Vec4::operator +(Vec4 v) {
    return Vec4(x+v.getX(), y+v.getY(), z+v.getZ());
}

Vec4 Vec4::operator -(Vec4 v) {
    return Vec4(x-v.getX(), y-v.getY(), z-v.getZ());
}

Vec4 Vec4::operator *(double d) {
    return Vec4(d*x, d*y, d*z, d*w);
}

Vec4 Vec4::operator /(double d)
{
    return Vec4(x/d, y/d, z/d, w/d);
}

double Vec4::operator *(Vec4 v) {
    return x*v.getX() + y*v.getY() + z*v.getZ() + w*v.getMode();
}

Vec4 Vec4::operator %(Vec4 v) {
    double x1 = (y*v.getZ())-(z*v.getY());
    double y1 = -((x*v.getZ())-(z*v.getX()));
    double z1 = (x*v.getY())-(y*v.getX());
    return Vec4(x1,y1,z1);
}



