#include "render.h"

Render::Render()
{
    scene = Scene();
    canvas = Canvas();
    samples = 1;
    depth = 4;
    depthOfField = 0;
    backgroundColor = Color();
    shadowDensity = 0.5;
    softShadows = 0;
    useBB = false;
}

Render::Render(Scene scene, Canvas canvas)
{
    this->scene = scene;
    this->canvas = canvas;
    this->samples = 1;
    this->backgroundColor = Color();
    this->shadowDensity = 0.5;
    this->depth = 4;
    this->depthOfField = 0;
    this->softShadows = 0;
    this->useBB = false;
}

Canvas Render::getCanvas()
{
    return canvas;
}

void Render::setCanvas(Canvas &value)
{
    canvas = value;
}

Scene Render::getScene()
{
    return scene;
}

void Render::setScene(Scene &value)
{
    scene = value;
}

unsigned int Render::getSamples()
{
    return samples;
}

void Render::setSamples(unsigned int value)
{
    samples = value;
}

Color Render::getBackgroundColor()
{
    return backgroundColor;
}

void Render::setBackgroundColor(Color value)
{
    backgroundColor = value;
}

double Render::getShadowDensity()
{
    return shadowDensity;
}

void Render::setShadowDensity(double value)
{
    shadowDensity = value;
}

void Render::useBoundingBox(bool use)
{
    this->useBB = use;
}

bool Render::getUseBoundingBox() {
    return useBB;
}

unsigned int Render::getDepth()
{
    return depth;
}

void Render::setDepth(unsigned int value)
{
    depth = value;
}

double Render::getDepthOfField()
{
    return depthOfField;
}

void Render::setDepthOfField(double value)
{
    this->depthOfField = value;
}
double Render::getSoftShadows()
{
    return softShadows;
}

void Render::setSoftShadows(double value)
{
    softShadows = value;
}


void Render::renderScene()
{
    if (useBB) scene.generateBoundingBox();
    double total = canvas.getWidth()*canvas.getWidth();
    int count = 1;
    for (unsigned int i = 0; i < canvas.getWidth(); i++) {
        for (unsigned int j = 0; j < canvas.getHeight(); j++) {
            canvas.setPixel(i,j,getPixelColor(i,j));
        }
    }
}

Color Render::getPixelColor(int i, int j)
{
    Color total = Color();
    double w = scene.getCamera().getWidth();
    double h = scene.getCamera().getHeight();
    double stepX = scene.getCamera().getWidth()/canvas.getWidth();
    double stepY = scene.getCamera().getHeight()/canvas.getHeight();

    for (unsigned int k = 0; k < samples; k++) {
        double dX = stepX*(1+2*i-canvas.getWidth())/2 + fRand(-stepX/2,stepX/2);
        double dY = stepY*(canvas.getHeight()-1-2*j)/2 + fRand(-stepY/2,stepY/2);
        double dZ = scene.getCamera().getProjectionPlane();

        Vec4 origin = Vec4(fRand(-depthOfField/2000,depthOfField/2000),fRand(-depthOfField/2000,depthOfField/2000),0,1);
        Vec4 direction = Vec4(dX,dY,dZ) - origin;

        direction.normalize();

        Ray ray = Ray(scene.getCamera().rayCameraToWorld(origin),
                      scene.getCamera().rayCameraToWorld(direction));

        total = total + rayCaster(ray, depth);
    }

    return total/samples;
}

Color Render::rayCaster(Ray ray, int depth)
{
    Color color = Color();

    if (depth > 0) {
        pair<Vec4,Vec4> pairResult = scene.checkIntersect(ray,useBB);
        Vec4 result = pairResult.first;
        Vec4 point = ray.findPoint(result.getY());
        int objIndex = result.getZ();
        Object3D *object;

        if (result.getX() > 0) {
            double shadowInt = notReachedLight(point, objIndex);
            if (shadowInt > 0) {
                Color shadow = Color(shadowDensity,shadowDensity,shadowDensity);
                if (scene.getObjAt(objIndex)->isTextured()) {
                    if (scene.getObjAt(objIndex)->getTextIntensity() < 1) {
                        Color phong = calculatePhong(objIndex,point,pairResult.second,true) + shadow;
                        Color texture = calculateTexture(objIndex,pairResult.second,true) + shadow;
                        color = color + texture*scene.getObjAt(objIndex)->getTextIntensity() +
                                phong*(1 - scene.getObjAt(objIndex)->getTextIntensity());
                    } else {
                        color = color + calculateTexture(objIndex,pairResult.second,true) + shadow;
                    }
                } else {
                    color = color + calculatePhong(objIndex,point,pairResult.second,true) + shadow;
                }

                color = color - shadow*shadowInt;
            } else {
                if (scene.getObjAt(objIndex)->isTextured()) {
                    if (scene.getObjAt(objIndex)->getTextIntensity() < 1) {
                        Color phong = calculatePhong(objIndex,point,pairResult.second,false);
                        Color texture = calculateTexture(objIndex,pairResult.second,false);
                        color = color + texture*scene.getObjAt(objIndex)->getTextIntensity() +
                                phong*(1 - scene.getObjAt(objIndex)->getTextIntensity());
                    } else {
                        color = color + calculateTexture(objIndex,pairResult.second,false);
                    }
                } else {
                    color = color + calculatePhong(objIndex,point,pairResult.second,false);
                }
            }

            object = scene.getObjAt(objIndex);
            if (object->getMaterial().getReflect() > 0) {
                double reflect = object->getMaterial().getReflect();
                color = color*(1-reflect) + getReflection(ray,result,pairResult.second,depth)*reflect;
            }

            if (object->getMaterial().getIor() != 0) {
                double dissolve = object->getMaterial().getDissolve();
                color = color*dissolve + getRefracted(ray,result,pairResult.second,depth)*(1-dissolve);
            }
        } else {
            return backgroundColor;
        }
    }

    return color;
}

Color Render::getRefracted(Ray ray, Vec4 result, Vec4 objNormal, int depth) {
    Object3D *object = scene.getObjAt(result.getZ());
    Vec4 point = ray.findPoint(result.getY());
    Vec4 normal = object->getNormal(objNormal);

    Vec4 eye = scene.getCamera().getOrigin() - point;
    eye.normalize();

    double iorFrac = 1/object->getMaterial().getIor();
    double iorFracQuad = 1/pow(object->getMaterial().getIor(),2);

    Vec4 refractedDir = normal*(iorFrac*(normal*eye) - sqrt(1-iorFracQuad*(1-pow(normal*eye,2)))) - eye*iorFrac;
    refractedDir.normalize();

    Ray refractedRay = Ray(point, refractedDir);

    return rayCaster(refractedRay,depth-1);
}

Color Render::getReflection(Ray ray, Vec4 result, Vec4 objNormal, int depth) {
    Object3D *object = scene.getObjAt(result.getZ());
    Vec4 point = ray.findPoint(result.getY());
    Vec4 normal = object->getNormal(objNormal);
    Vec4 eye = scene.getCamera().getOrigin() - point;
    eye.normalize();
    Vec4 reflectDir = (normal*(normal*eye)*2) - eye;
    double glossy = object->getMaterial().getGlossy();
    reflectDir = reflectDir + Vec4(fRand(-glossy,glossy),fRand(-glossy,glossy),fRand(-glossy,glossy));
    reflectDir.normalize();

    Ray reflectedRay = Ray(point,reflectDir);
    return rayCaster(reflectedRay,depth-1);
}

double Render::notReachedLight(Vec4 point, int objIndex)
{
    double l = 0;
    for (unsigned int i = 0; i < scene.lightNum(); i++) {
        Light* light = scene.getLightAt(i);

        Vec4 dir = light->getOrigin() + Vec4(fRand(-softShadows,softShadows),
                                             fRand(-softShadows,softShadows),
                                             fRand(-softShadows,softShadows),1) - point;

        double lightDist = dir.calculateNorm();
        dir.normalize();

        Ray ray = Ray(point,dir);
        Vec4 result = scene.checkIntersect(ray,useBB).first;

        double intersectDist = (ray.findPoint(result.getY()) - point).calculateNorm();

        if ((result.getX() == 1)&&(result.getZ() != objIndex)&&(intersectDist < lightDist)) {
            l += light->getIntensity();
            double dissolve = scene.getObjAt(objIndex)->getMaterial().getDissolve();
            if (dissolve < 1) l = l*dissolve;
        }
    }
    return l;
}

Color Render::calculateTexture(int objIndex, Vec4 point, bool shadow) {
    Object3D *object = scene.getObjAt(objIndex);
    Color color;

    color = object->getTextureColor(point);

    if (shadow) color = color - Color(shadowDensity,shadowDensity,shadowDensity);

    return color;
}

Color Render::calculatePhong(int objIndex, Vec4 point, Vec4 objNormal, bool shadow)
{
    Object3D* object = scene.getObjAt(objIndex);

    Vec4 normal = object->getNormal(objNormal);

    Vec4 eye = scene.getCamera().getOrigin() - point;
    eye.normalize();

    Color Ia,Id,Is;
    Ia = Id = Is = Color();

    for (unsigned int l = 0; l < scene.lightNum(); l++) {
        Light* light = scene.getLightAt(l);

        Vec4 lightDir = light->getOrigin() - point;
        lightDir.normalize();
        Vec4 reflect = (normal*(normal*lightDir)*2) - lightDir;
        reflect.normalize();

        Ia = Ia + scene.getAmbientLight()->getMaterial().getAmbient()*
                  object->getMaterial().getAmbient();
        if (!shadow) Id = Id + light->getMaterial().getDiffuse()*
                               object->getMaterial().getDiffuse()*qMax<double>(normal*lightDir,0)*
                               light->getIntensity();
        if (!shadow) Is = Is + light->getMaterial().getSpecular()*
                               object->getMaterial().getSpecular()*
                               pow(qMax<double>(reflect*eye,0),object->getMaterial().getShininess())*
                               light->getIntensity();
    }

    return Ia + Id + Is;
}

double Render::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


