#include "camera.h"

Camera::Camera() : Object3D()
{
    lookAt = Vec4();
    vup = Vec4(0,1,0);
    height = 2;
    width = 2;
    projectionPlane = -1;
}

Camera::Camera(Vec4 lookAt, Vec4 vup, double height, double width, double projectionPlane) : Object3D()
{
    lookAt.normalize();
    vup.normalize();

    this->lookAt = lookAt;
    this->vup = vup;
    this->height = height;
    this->width = width;
    this->projectionPlane = projectionPlane;
}

Vec4 Camera::getLookAt()
{
    return getCLTMatrix()*lookAt;
}

void Camera::setLookAt(Vec4 lookAt)
{
    this->lookAt = lookAt;
}

Vec4 Camera::getVup()
{
    return getCLTMatrix()*vup;
}

void Camera::setVup(Vec4 vup)
{
    this->vup = vup;
}
double Camera::getHeight()
{
    return height;
}

void Camera::setHeight(double value)
{
    height = value;
}
double Camera::getWidth()
{
    return width;
}

void Camera::setWidth(double value)
{
    width = value;
}
double Camera::getProjectionPlane()
{
    return projectionPlane;
}

void Camera::setProjectionPlane(double value)
{
    projectionPlane = value;
}

Vec4 Camera::rayCameraToWorld(Vec4 v) {
    Vec4 z = (origin - lookAt).normalize();
    Vec4 x = (vup % z).normalize();
    Vec4 y = (z % x).normalize();

    Mtx4 m = Mtx4();

    m.setLine(0,x);
    m.setLine(1,y);
    m.setLine(2,z);
    m.transpose();
    m.setValue(0,3,origin.getX());
    m.setValue(1,3,origin.getY());
    m.setValue(2,3,origin.getZ());
    m.setLine(3,0,0,0,1);

    //m.print();

    return (m*v);
}






