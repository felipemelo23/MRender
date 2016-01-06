#include <Objects/camera.h>
#include <Objects/light.h>
#include <Objects/sphere.h>
#include <Objects/object3d.h>
#include <Objects/box.h>
#include <Objects/boundingbox.h>
#include <vector>

#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    Scene();
    Scene(vector<Object3D *> *objects, vector<Light *> *lights, Camera camera);

    int objNum();
    void addObject(Object3D* o);
    Object3D* getObjAt(int id);
    vector<Object3D*>* getObjects();
    void setObjAt(int i, Object3D* o);
    void setObjects(vector<Object3D*> *o);

    int lightNum();
    void addLight(Light* l);
    Light* getLightAt(int i);
    vector<Light*>* getLights();
    void setLightAt(int i, Light* l);
    void setLights(vector<Light*> *l);

    Camera getCamera();
    void setCamera(Camera &value);

    /*
     * The three field of result vector  is
     * x -> 1 if ray intersected any object
     * y -> t value of intersection
     * z -> index of intersected object
     */
    pair<Vec4,Vec4> checkIntersect(Ray ray, bool useBB);

    Light *getAmbientLight();
    void setAmbientLight(Light *value);

    void generateBoundingBox();

    BoundingBox *getRoot();
    void setRoot(BoundingBox *value);

private:
    vector<Object3D*> *objects;
    BoundingBox *root;
    vector<Light*> *lights;
    Light *ambient;
    Camera camera;
    int lastObjId;

    void sortObjects();
    vector<BoundingBox *> mergeBoundingBoxes(vector<BoundingBox *> bblist);
};

#endif // SCENE_H
