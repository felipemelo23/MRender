#include "boundingbox.h"

BoundingBox::BoundingBox(BoundingBox *leftChild, BoundingBox *rightChild)
{
    min.setX(qMin<double>(leftChild->getMin().getX(),rightChild->getMin().getX()));
    min.setY(qMin<double>(leftChild->getMin().getY(),rightChild->getMin().getY()));
    min.setZ(qMin<double>(leftChild->getMin().getZ(),rightChild->getMin().getZ()));

    max.setX(qMax<double>(leftChild->getMax().getX(),rightChild->getMax().getX()));
    max.setY(qMax<double>(leftChild->getMax().getY(),rightChild->getMax().getY()));
    max.setZ(qMax<double>(leftChild->getMax().getZ(),rightChild->getMax().getZ()));

    object = NULL;
    left = leftChild;
    right = rightChild;
    leaf = false;
}

BoundingBox::BoundingBox(Object3D *obj)
{
    Vec4 objMin = obj->getMin();
    Vec4 objMax = obj->getMax();

    min.setX(objMin.getX());
    min.setY(objMin.getY());
    min.setZ(objMin.getZ());

    max.setX(objMax.getX());
    max.setY(objMax.getY());
    max.setZ(objMax.getZ());

    object = obj;
    left = NULL;
    right = NULL;
    leaf = true;
}

pair<Vec4, Vec4> BoundingBox::checkIntersect(Ray ray)
{
    double txmin, txmax, tymin, tymax, tzmin, tzmax;

    Vec4 origin = ray.getOrigin();

    if ((origin.getX() > min.getX()) && (origin.getX() < max.getX()) &&
        (origin.getY() > min.getY()) && (origin.getY() < max.getY()) &&
        (origin.getZ() > min.getZ()) && (origin.getZ() < max.getZ())) {
        return checkChildrenIntersect(ray);
    }

    if (ray.getDirection().getX() >= 0) {
        txmin = (min.getX() - ray.getOrigin().getX())/ray.getDirection().getX();
        txmax = (max.getX() - ray.getOrigin().getX())/ray.getDirection().getX();
    } else {
        txmin = (max.getX() - ray.getOrigin().getX())/ray.getDirection().getX();
        txmax = (min.getX() - ray.getOrigin().getX())/ray.getDirection().getX();
    }

    if (ray.getDirection().getY() >= 0) {
        tymin = (min.getY() - ray.getOrigin().getY())/ray.getDirection().getY();
        tymax = (max.getY() - ray.getOrigin().getY())/ray.getDirection().getY();
    } else {
        tymin = (max.getY() - ray.getOrigin().getY())/ray.getDirection().getY();
        tymax = (min.getY() - ray.getOrigin().getY())/ray.getDirection().getY();
    }

    if (ray.getDirection().getZ() >= 0) {
        tzmin = (min.getZ() - ray.getOrigin().getZ())/ray.getDirection().getZ();
        tzmax = (max.getZ() - ray.getOrigin().getZ())/ray.getDirection().getZ();
    } else {
        tzmin = (max.getZ() - ray.getOrigin().getZ())/ray.getDirection().getZ();
        tzmax = (min.getZ() - ray.getOrigin().getZ())/ray.getDirection().getZ();
    }

    double tmin = maxValue3d(txmin,tymin,tzmin);
    double tmax = minValue3d(txmax,tymax,tzmax);

    if (tmin > tmax) return make_pair(Vec4(),Vec4());

    Vec4 pMin = ray.findPoint(tmin);
    Vec4 pMax = ray.findPoint(tmax);

    return checkChildrenIntersect(ray);
}

pair<Vec4, Vec4> BoundingBox::checkChildrenIntersect(Ray ray) {
    if (object != NULL) {
        return object->checkIntersect(ray);
    } else {
        pair<Vec4, Vec4> resultLeft, resultRight;

        resultLeft = resultRight = make_pair(Vec4(),Vec4());

        if (left != NULL) {
            resultLeft = left->checkIntersect(ray);
        }
        if (right != NULL) {
            resultRight = right->checkIntersect(ray);
        }

        if (((resultLeft.first.getX() == 0) || (resultLeft.first.getY() <= 0.001)) &&
            ((resultRight.first.getX() != 0) && (resultRight.first.getY() > 0.001))) {
            return resultRight;
        }

        if (((resultRight.first.getX() == 0) || (resultRight.first.getY() <= 0.001)) &&
            ((resultLeft.first.getX() != 0) && (resultLeft.first.getY() > 0.001))) {
            return resultLeft;
        }

        if (((resultLeft.first.getX() == 0) || (resultLeft.first.getY() <= 0.001)) &&
            ((resultRight.first.getX() == 0) || (resultRight.first.getY() <= 0.001))) {
            return make_pair(Vec4(),Vec4());
        }

        if (resultLeft.first.getY() < resultRight.first.getY()) {
            return resultLeft;
        } else {
            return resultRight;
        }

//        if ((resultLeft.first.getX() != 0) && (resultRight.first.getX() != 0)) {
//            if (resultLeft.first.getY() < resultRight.first.getY()) {
//                return resultLeft;
//            } else {
//                return resultRight;
//            }
//        } else if (resultLeft.first.getX() == 0){
//            return resultRight;
//        } else if (resultRight.first.getX() == 0) {
//            return resultLeft;
//        } else {
//            return make_pair(Vec4(),Vec4());
//        }
    }
}

Vec4 BoundingBox::getMin() const
{
    return min;
}

void BoundingBox::setMin(const Vec4 &value)
{
    min = value;
}
Vec4 BoundingBox::getMax() const
{
    return max;
}

void BoundingBox::setMax(const Vec4 &value)
{
    max = value;
}

Object3D* BoundingBox::getObject()
{
    return object;
}

void BoundingBox::setObject(Object3D *value)
{
    object = value;
}
bool BoundingBox::getLeaf() const
{
    return leaf;
}

void BoundingBox::setLeaf(bool value)
{
    leaf = value;
}
BoundingBox *BoundingBox::getLeft() const
{
    return left;
}

void BoundingBox::setLeft(BoundingBox *value)
{
    left = value;
}
BoundingBox *BoundingBox::getRight() const
{
    return right;
}

void BoundingBox::setRight(BoundingBox *value)
{
    right = value;
}
QString BoundingBox::getId() const
{
    return id;
}

void BoundingBox::setId(const QString &value)
{
    id = value;
}

QString BoundingBox::print()
{
    if (object == NULL) {
        return "BB: left(" + left->print() + "), right(" + right->print() + ")";
    } else {
        return QString(object->getId()+48);
    }
}

double BoundingBox::minValue3d(double a, double b, double c) {
    double value = qMin(a,b);
    return qMin(value,c);
}

double BoundingBox::maxValue3d(double a, double b, double c) {
    return qMax(qMax(a,b),c);
}










