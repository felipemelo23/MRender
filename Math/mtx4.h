#ifndef MTX4_H
#define MTX4_H

#include "vec4.h"

class Mtx4
{
public:
    static const int LINES = 0;
    static const int COLUMNS = 1;

    Mtx4();
    Mtx4(double m11, double m12, double m13, double m14,
         double m21, double m22, double m23, double m24,
         double m31, double m32, double m33, double m34,
         double m41, double m42, double m43, double m44);
    Mtx4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4, int mode=0);

    void loadIdentity();
    void transpose();
    Mtx4 copy();

    double getValue(int i, int j);
    void setValue(int i, int j, double value);

    Vec4 getLine(int i);
    void setLine(int i, Vec4 line);
    void setLine(int i, double l1, double l2, double l3, double l4);

    Vec4 getColumn(int i);
    void setColumn(int i, Vec4 column);
    void setColumn(int i, double c1, double c2, double c3, double c4);

    void mtxBasisChange(Vec4 baseX, Vec4 baseY, Vec4 baseZ, Vec4 baseO);
    void mtxBasisChangeInv(Vec4 baseX, Vec4 baseY, Vec4 baseZ, Vec4 baseO);

    void print();
    void removeNoise();

    Mtx4 operator + (Mtx4 m);
    Mtx4 operator - (Mtx4 m);
    Mtx4 operator * (double d);
    Mtx4 operator * (Mtx4 m);
    Vec4 operator * (Vec4 v);

protected:
    double m[4][4];



};

#endif // MTX4_H
