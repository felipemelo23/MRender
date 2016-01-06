#include "object3d.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera : public Object3D
{
public:
    Camera();
    Camera(Vec4 lookAt, Vec4 vup, double height=2, double width=2, double projectionPlane=-1);

    Vec4 getLookAt();
    void setLookAt(Vec4 lookAt);

    Vec4 getVup();
    void setVup(Vec4 vup);

    double getHeight();
    void setHeight(double value);

    double getWidth();
    void setWidth(double value);

    double getProjectionPlane();
    void setProjectionPlane(double value);
    Vec4 rayCameraToWorld(Vec4 v);
private:
    Vec4 lookAt;
    Vec4 vup;
    double height;
    double width;
    double projectionPlane;
};

#endif // CAMERA_H
