#include <Math/mtx4.h>
#include <Render/material.h>
#include <Render/ray.h>
#include <Render/texture.h>
#include <stdlib.h>
#include <QtGlobal>
#include <QString>
#include <utility>
#include <QImage>

#ifndef OBJECT3D_H
#define OBJECT3D_H

using namespace std;

class Object3D
{
public:
    Object3D(QString name="ObjectGeneric");
    Object3D(Material material, QString name="ObjectGeneric");

    int getId();
    void setId(int id);

    Material getMaterial();
    void setMaterial(const Material &value);

    Mtx4 getCLTMatrix();
    Mtx4 getCLTMatrixInv(Vec4 point);
    Mtx4 getCNMatrix();
    Mtx4 getCNMatrixInv();

    void applyTranslate(double x, double y, double z);
    void applyRotate(double ang, bool x, bool y, bool z);
    void applyScale(double x, double y, double z);

    virtual Vec4 getNormal(Vec4 point);

    /*
     * The ray is in world coordinates and it's converted inside the function
     * and the function returns a vector whose x component contains a positive value
     * if the ray intersects the object and zero if don't, further the
     * y vector output component is the T value that is used to calculate the point in
     * world coordinates which intersects the object.
     */
    virtual pair<Vec4,Vec4> checkIntersect(Ray raySend);
    virtual Vec4 getMin();
    virtual Vec4 getMax();
    virtual Color getTextureColor(Vec4 point);

    virtual Vec4 getOrigin();
    void setOrigin(Vec4 value);

    QString getType();
    void setType(QString &value);

    QString getName();
    void setName(QString &value);

    Vec4 getRot();

    Vec4 getScale();

    Vec4 getCLTMatrixInvDir(Vec4 point);
    Vec4 getCLTMatrixInvOrigin(Vec4 point);
    Mtx4 getCLTMatrixInv();
    Vec4 getCLTMatrixDir(Vec4 dir);
    Vec4 getCLTMatrixOrigin(Vec4 origin);

    Texture getTexture();
    void setTexture(Texture &value);

    bool isTextured();

    void setTextIntensity(double textIntensity);
    double getTextIntensity();

protected:
    Texture texture;
    bool hasTexture;
    double textIntensity;
    Vec4 origin;
    Vec4 rot;
    int id;
    Material material;
    QString type;
    QString name;

    Mtx4 translate;
    Mtx4 translateInv;
    Mtx4 rotate;
    Mtx4 rotateInv;
    Mtx4 scale;
    Mtx4 scaleInv;

//    Mtx4 cltMatrix; //Concatenated Linear Transformation Matrix. Object->World
//    Mtx4 cltMatrixInv; //Concatenaded Linear Transformation Matrix Inverse. World->Object
//    Mtx4 cnMatrix; //Concatenaded Normal Matrix. Object->World
//    Mtx4 cnMatrixInv; //Concatenaded Normal Matrix Inverse. World->Object

    void instantiateMatrices();
    bool isAlmost(double n1, double n2);
};

#endif // OBJECT3D_H
