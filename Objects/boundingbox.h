#include "object3d.h"
#include <iostream>
#include <QtGlobal>

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

using namespace std;

class BoundingBox : public Object3D
{
public:
    BoundingBox(BoundingBox *leftChild, BoundingBox *rightChild);
    BoundingBox(Object3D *obj);

    virtual pair<Vec4,Vec4> checkIntersect(Ray ray);

    Vec4 getMin() const;
    void setMin(const Vec4 &value);

    Vec4 getMax() const;
    void setMax(const Vec4 &value);

    Object3D *getObject();
    void setObject(Object3D *value);

    bool getLeaf() const;
    void setLeaf(bool value);

    BoundingBox *getLeft() const;
    void setLeft(BoundingBox *value);

    BoundingBox *getRight() const;
    void setRight(BoundingBox *value);

    QString getId() const;
    void setId(const QString &value);

    QString print();

private:
    QString id;
    Vec4 min;
    Vec4 max;
    BoundingBox *left;
    BoundingBox *right;
    Object3D *object;
    bool leaf;
    pair<Vec4, Vec4> checkChildrenIntersect(Ray ray);
    double minValue3d(double a, double b, double c);
    double maxValue3d(double a, double b, double c);
};

#endif // BOUNDINGBOX_H
