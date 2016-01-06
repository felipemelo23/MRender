#include "canvas.h"
#include "scene.h"
#include <QtGlobal>

#ifndef RENDER_H
#define RENDER_H

class Render
{
public:
    Render();
    Render(Scene scene, Canvas canvas);

    Canvas getCanvas();
    void setCanvas(Canvas &value);

    Scene getScene();
    void setScene(Scene &value);

    void renderScene();

    unsigned int getSamples();
    void setSamples(unsigned int value);

    Color getBackgroundColor();
    void setBackgroundColor(Color value);

    double getShadowDensity();
    void setShadowDensity(double value);

    void useBoundingBox(bool use);

    unsigned int getDepth();
    void setDepth(unsigned int value);

    double getDepthOfField();
    void setDepthOfField(double value);

    double getSoftShadows();
    void setSoftShadows(double value);

    bool getUseBoundingBox();
private:
    bool useBB;
    double softShadows;
    double depthOfField;
    Canvas canvas;
    Scene scene;
    Color backgroundColor;
    unsigned int samples;
    unsigned int depth;
    double shadowDensity;

    Color getPixelColor(int i, int j);
    Color rayCaster(Ray ray, int depth);
    /**
     * i -> intersected object index
     * point -> point in world coordinates where the ray intersected the object
     **/
    Color calculatePhong(int objIndex, Vec4 point, Vec4 objNormal, bool shadow);
    double fRand(double fMin, double fMax);
    double notReachedLight(Vec4 point, int objIndex);
    Color getReflection(Ray ray, Vec4 result,Vec4 objNormal, int depth);
    Color getRefracted(Ray ray, Vec4 result, Vec4 objNormal, int depth);
    Color calculateTexture(int objIndex, Vec4 point, bool shadow);
    Color calculatePlaneTexture(int objIndex, Vec4 point);
};

#endif // RENDER_H
