#include "object3d.h"

Object3D::Object3D(QString name)
{
    id = rand();
    origin = Vec4();
    material = Material();
    instantiateMatrices();
    rot = Vec4();
    hasTexture = false;
    textIntensity = 0.9;
}

Object3D::Object3D(Material material, QString name)
{
    id = rand();
    origin = Vec4();
    this->material = material;
    instantiateMatrices();
    rot = Vec4();
    hasTexture = false;
    textIntensity = 0.9;
}

Vec4 Object3D::getOrigin()
{
    return getCLTMatrix()*origin;
}

void Object3D::setOrigin(Vec4 value)
{
    origin = value;
}
QString Object3D::getType()
{
    return type;
}

void Object3D::setType(QString &value)
{
    type = value;
}

QString Object3D::getName()
{
    return name;
}

void Object3D::setName(QString &value)
{
    name = value;
}
Vec4 Object3D::getRot()
{
    return rot;
}

Vec4 Object3D::getScale()
{
    return Vec4(scale.getValue(0,0),scale.getValue(1,1),scale.getValue(2,2));
}

int Object3D::getId()
{
    return id;
}

void Object3D::setId(int id)
{
    this->id = id;
}

Material Object3D::getMaterial()
{
    return material;
}

void Object3D::setMaterial(const Material &value)
{
    material = value;
}

Mtx4 Object3D::getCLTMatrix()
{
    return translate*rotate*scale;
}

Vec4 Object3D::getCLTMatrixOrigin(Vec4 origin) {
    origin = scale*origin;
    origin = rotate*origin;
    origin = translate*origin;
    return origin;
}
Texture Object3D::getTexture()
{
    return texture;
}

void Object3D::setTexture(Texture &value)
{
    hasTexture = true;
    texture = value;
}

bool Object3D::isTextured()
{
    return hasTexture;
}

void Object3D::setTextIntensity(double textIntensity)
{
    this->textIntensity = textIntensity;
}

double Object3D::getTextIntensity()
{
    return textIntensity;
}

Vec4 Object3D::getCLTMatrixDir(Vec4 dir) {
    dir = scale*dir;
    dir = rotate*dir;
    return dir;
}

Mtx4 Object3D::getCLTMatrixInv()
{
    return (scaleInv*rotateInv)*translateInv;
}

Vec4 Object3D::getCLTMatrixInvOrigin(Vec4 point) {
    point = translateInv*point;
    point = rotateInv*point;
    point = scaleInv*point;

    return point;
}

Vec4 Object3D::getCLTMatrixInvDir(Vec4 point) {
    point = rotateInv*point;
    point = scaleInv*point;

    return point;
}

Mtx4 Object3D::getCNMatrix()
{
    return rotate*scaleInv;
}

Mtx4 Object3D::getCNMatrixInv()
{
    return scale*rotateInv;
}

void Object3D::applyTranslate(double x, double y, double z)
{
    Mtx4 t = Mtx4();
    Mtx4 ti = Mtx4();
    t.setColumn(3,x,y,z,1);
    ti.setColumn(3,-x,-y,-z,1);

    translate = t*translate;
    translateInv = translateInv*ti;
}

void Object3D::applyRotate(double ang, bool x, bool y, bool z)
{
    Mtx4 r;
    Mtx4 ri;

    double degree = ang;
    ang = -(ang*M_PI)/180;

    if (x && !y && !z) {
        r = Mtx4(1,    0,       0,    0,
                 0, cos(ang),sin(ang),0,
                 0,-sin(ang),cos(ang),0,
                 0,    0    ,   0,    1);
        rot.setX(rot.getX()+degree);
    } else if (!x && y && !z) {
        r = Mtx4(cos(ang),0,-sin(ang),0,
                    0,    1,    0,    0,
                 sin(ang),0, cos(ang),0,
                    0,    0,    0,    1);
        rot.setY(rot.getY()+degree);
    } else if (!x && !y && z) {
        r = Mtx4( cos(ang),sin(ang),0,0,
                 -sin(ang),cos(ang),0,0,
                     0,       0,    1,0,
                     0,       0,    0,1);
        rot.setZ(rot.getZ()+degree);
    }
    ri = r.copy();
    ri.transpose();

    rotate = r*rotate;
    rotateInv = rotateInv*ri;
}

void Object3D::applyScale(double x, double y, double z)
{
    Mtx4 s = Mtx4(x,0,0,0,
                  0,y,0,0,
                  0,0,z,0,
                  0,0,0,1);

    Mtx4 si = Mtx4(1/x,0,0,0,
                   0,1/y,0,0,
                   0,0,1/z,0,
                   0,0,0,1);

    scale = s;
    scaleInv = si;
}

Vec4 Object3D::getNormal(Vec4 point) {
    cout << "Wrong Way" << endl;
}

pair<Vec4, Vec4> Object3D::checkIntersect(Ray raySend){
    cout << "Wrong Way" << endl;
}

Vec4 Object3D::getMin(){}

Vec4 Object3D::getMax(){}

Color Object3D::getTextureColor(Vec4 point){}

void Object3D::instantiateMatrices()
{
    translate = Mtx4();
    rotate = Mtx4();
    scale = Mtx4();
    translateInv = Mtx4();
    rotateInv = Mtx4();
    scaleInv = Mtx4();
}

bool Object3D::isAlmost(double n1, double n2) {
    if ((fabs(n1-n2) <= 0.0000001)&&(fabs(n1-n2) >= 0)) {
        return true;
    }
    return false;
}

