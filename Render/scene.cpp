#include "scene.h"

Scene::Scene()
{
    objects = new vector<Object3D*>();
    lights = new vector<Light*>();
    ambient = new Light();
    camera = Camera();
    lastObjId = 0;
}

Scene::Scene(vector<Object3D *> *objects, vector<Light *> *lights, Camera camera)
{
    this->objects = objects;
    this->lights = lights;
    this->camera = camera;
    this->ambient = new Light();
    this->lastObjId = 0;
}

int Scene::objNum()
{
    return objects->size();
}

void Scene::addObject(Object3D *o)
{
    objects->push_back(o);
    o->setId(lastObjId);
    lastObjId++;
}

Object3D *Scene::getObjAt(int id)
{
    for (int i = 0; i < objNum(); i++) {
        Object3D *obj = objects->at(i);
        if (obj->getId() == id) return obj;
    }

    return NULL;
}

vector<Object3D *> *Scene::getObjects()
{
    return objects;
}

void Scene::setObjAt(int i, Object3D *o)
{
    objects->at(i) = o;
}

void Scene::setObjects(vector<Object3D *> *o)
{
    objects = o;
}

int Scene::lightNum()
{
    return lights->size();
}

void Scene::addLight(Light *l)
{
    lights->push_back(l);
}

Light *Scene::getLightAt(int i)
{
    return lights->at(i);
}

vector<Light *> *Scene::getLights()
{
    return lights;
}

void Scene::setLightAt(int i, Light *l)
{
    lights->at(i) = l;
}

void Scene::setLights(vector<Light *> *l)
{
    lights = l;
}

Camera Scene::getCamera()
{
    return camera;
}

void Scene::setCamera(Camera &value)
{
    camera = value;
}

pair<Vec4, Vec4> Scene::checkIntersect(Ray ray, bool useBB)
{
    if (useBB) {
        pair<Vec4,Vec4> result = root->checkIntersect(ray);
        if ((result.first.getX() > 0)&&(result.first.getY() > 0.001)) {
            //cout << result.first.getY() << endl;
            return result;
        }
        return make_pair(Vec4(),Vec4());
    } else {
        double t = INT_MAX;
        int object = 0;
        bool reached = false;
        pair<Vec4,Vec4> result = make_pair(Vec4(),Vec4());
        Vec4 objNormal = Vec4();

        for (int i = 0; i < objects->size(); i++) {
            result = getObjAt(i)->checkIntersect(ray);

            if ((result.first.getX() > 0)&&(result.first.getY() > 0.001)) {
                if (result.first.getY() <= t) {
                    reached = true;
                    object = i;
                    t = result.first.getY();
                    objNormal = result.second;
                }
            }
        }

        if (reached){
            return make_pair(Vec4(1,t,object),objNormal);
        }
        return make_pair(Vec4(),Vec4());
    }
}
Light *Scene::getAmbientLight()
{
    return ambient;
}

void Scene::setAmbientLight(Light *value)
{
    ambient = value;
}

void Scene::sortObjects()
{
    for (int i = 0; i < objNum()-1; i++) {
        for (int j = i+1; j < objNum(); j++) {
            if (objects->at(i)->getOrigin().getX() > objects->at(j)->getOrigin().getX()) {
                Object3D *aux = objects->at(i);
                objects->at(i) = objects->at(j);
                objects->at(j) = aux;
            }
        }
    }
}

vector<BoundingBox *> Scene::mergeBoundingBoxes(vector<BoundingBox *> bblist)
{
    sortObjects();

    vector<BoundingBox*> result;
    result = vector<BoundingBox*>();

    while (bblist.size() > 1) {
        BoundingBox *bb1 = bblist.back();
        bblist.pop_back();
        BoundingBox *bb2 = bblist.back();
        bblist.pop_back();
        result.push_back(new BoundingBox(bb1,bb2));
    }

    if (!bblist.empty()) {
        result.push_back(bblist.back());
        bblist.pop_back();
    }

    return result;
}

void Scene::generateBoundingBox()
{
    vector<BoundingBox*> bblist;
    bblist = vector<BoundingBox*>();

    for (int i = 0; i < objNum(); i++) {
        bblist.push_back(new BoundingBox(objects->at(i)));
    }

    while (bblist.size() > 1) {
        bblist = mergeBoundingBoxes(bblist);
    }

    root = bblist.front();
    cout << root->print().toStdString() << endl;
}
BoundingBox *Scene::getRoot()
{
    return root;
}

void Scene::setRoot(BoundingBox *value)
{
    root = value;
}


