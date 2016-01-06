#include <cmath>
#include <iostream>

#ifndef VEC4_H
#define VEC4_H

#define PRECISION 10e-9

using namespace std;

class Vec4
{
public:
    static const double VECTOR = 0.0f;
    static const double POINT = 1.0f;

    Vec4();
    Vec4(double x, double y, double z, double w = 0.0f);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

    double getMode() const;
    void setMode(double value);

    Vec4 normalize();
    double calculateNorm();

    void print();
    void removeNoise();

    Vec4 operator + (Vec4 v);
    Vec4 operator - (Vec4 v);
    Vec4 operator * (double d);
    Vec4 operator / (double d);
    double operator * (Vec4 v); //Dot Product
    Vec4 operator % (Vec4 v); //Cross Product

protected:
    double x,y,z,w;
};

#endif // VEC4_H
