#include "mtx4.h"

Mtx4::Mtx4() {
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            m[i][j] = 0;
        }
    }
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

Mtx4::Mtx4(double m11, double m12, double m13, double m14, double m21, double m22, double m23, double m24, double m31, double m32, double m33, double m34, double m41, double m42, double m43, double m44) {
    m[0][0] = m11;    m[0][1] = m12;    m[0][2] = m13;    m[0][3] = m14;
    m[1][0] = m21;    m[1][1] = m22;    m[1][2] = m23;    m[1][3] = m24;
    m[2][0] = m31;    m[2][1] = m32;    m[2][2] = m33;    m[2][3] = m34;
    m[3][0] = m41;    m[3][1] = m42;    m[3][2] = m43;    m[3][3] = m44;
}

Mtx4::Mtx4(Vec4 v1, Vec4 v2, Vec4 v3, Vec4 v4, int mode) {
    if (mode == LINES) {
        m[0][0] = v1.getX(); m[0][1] = v1.getY(); m[0][2] = v1.getZ(); m[0][3] = v1.getMode();
        m[1][0] = v2.getX(); m[1][1] = v2.getY(); m[1][2] = v2.getZ(); m[1][3] = v2.getMode();
        m[2][0] = v3.getX(); m[2][1] = v3.getY(); m[2][2] = v3.getZ(); m[2][3] = v3.getMode();
        m[3][0] = v4.getX(); m[3][1] = v4.getY(); m[3][2] = v4.getZ(); m[3][3] = v4.getMode();
    } else if (mode == COLUMNS) {
        m[0][0] = v1.getX(); m[0][1] = v2.getX(); m[0][2] = v3.getX(); m[0][3] = v4.getX();
        m[1][0] = v1.getY(); m[1][1] = v2.getY(); m[1][2] = v3.getY(); m[1][3] = v4.getY();
        m[2][0] = v1.getZ(); m[2][1] = v2.getZ(); m[2][2] = v3.getZ(); m[2][3] = v4.getZ();
        m[3][0] = v1.getMode(); m[3][1] = v2.getMode(); m[3][2] = v3.getMode(); m[3][3] = v4.getMode();
    }
}

void Mtx4::loadIdentity() {
    for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; i < 4; j++) {
            m[i][j] = 0;
        }
    }
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
}

void Mtx4::transpose()
{
    Mtx4 temp = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        temp.setColumn(i, this->getLine(i));
    }
    for (unsigned int i = 0; i < 4; i++) {
        this->setColumn(i, temp.getColumn(i));
    }
}

Mtx4 Mtx4::copy()
{
    Mtx4 temp = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        temp.setColumn(i,this->getColumn(i));
    }
    return temp;
}

double Mtx4::getValue(int i, int j) {
    return m[i][j];
}

void Mtx4::setValue(int i, int j, double value) {
    m[i][j] = value;
}

Vec4 Mtx4::getLine(int i) {
    return Vec4(m[i][0],m[i][1],m[i][2],m[i][3]);
}

void Mtx4::setLine(int i, Vec4 line) {
    m[i][0] = line.getX();
    m[i][1] = line.getY();
    m[i][2] = line.getZ();
    m[i][3] = line.getMode();
}

void Mtx4::setLine(int i, double l1, double l2, double l3, double l4) {
    m[i][0] = l1;
    m[i][1] = l2;
    m[i][2] = l3;
    m[i][3] = l4;
}

Vec4 Mtx4::getColumn(int i) {
    return Vec4(m[0][i],m[1][i],m[2][i],m[3][i]);
}

void Mtx4::setColumn(int i, Vec4 column) {
    m[0][i] = column.getX();
    m[1][i] = column.getY();
    m[2][i] = column.getZ();
    m[3][i] = column.getMode();
}

void Mtx4::setColumn(int i, double c1, double c2, double c3, double c4) {
    m[0][i] = c1;
    m[1][i] = c2;
    m[2][i] = c3;
    m[3][i] = c4;
}

void Mtx4::mtxBasisChange(Vec4 baseX, Vec4 baseY, Vec4 baseZ, Vec4 baseO) {
    setColumn(0,baseX);
    setColumn(1,baseY);
    setColumn(2,baseZ);
    setColumn(3,(baseX*baseO)*(-1),(baseY*baseO)*(-1),(baseZ*baseO)*(-1),1);
}

void Mtx4::mtxBasisChangeInv(Vec4 baseX, Vec4 baseY, Vec4 baseZ, Vec4 baseO) {
    setLine(0,baseX);
    setValue(0,3,baseO.getX());
    setLine(1,baseY);
    setValue(1,3,baseO.getY());
    setLine(2,baseZ);
    setValue(2,3,baseO.getZ());
    setLine(3,0,0,0,1);
}

void Mtx4::print() {
    for (unsigned int i = 0; i < 4; i++) {
        getLine(i).print();
    }
    cout << endl;
}

void Mtx4::removeNoise()
{
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            if (fabs(m[i][j]) <= PRECISION)
                m[i][j] = 0;
}

Mtx4 Mtx4::operator +(Mtx4 m) {
    Mtx4 result = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        result.setLine(i, getLine(i)+m.getLine(i));
    }
    return result;
}

Mtx4 Mtx4::operator -(Mtx4 m) {
    Mtx4 result = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        result.setLine(i, getLine(i)-m.getLine(i));
    }
    return result;
}

Mtx4 Mtx4::operator *(double d) {
    Mtx4 result = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        result.setLine(i, getLine(i)*d);
    }
    return result;
}

Vec4 Mtx4::operator *(Vec4 v) {
    double d[4];
    Vec4 result;
    for (unsigned int i = 0; i < 4; i++) {
        d[i] = getLine(i)*v;
    }
    result = Vec4(d[0],d[1],d[2],d[3]);
    return result;
}

Mtx4 Mtx4::operator *(Mtx4 m) {
    Mtx4 result = Mtx4();
    for (unsigned int i = 0; i < 4; i++) {
        result.setColumn(i,*this * m.getColumn(i));
    }
    return result;
}


