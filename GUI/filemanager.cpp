#include "filemanager.h"

#include <QDomDocument>

#include <Objects/cylinder.h>
#include <Objects/plane.h>

FileManager::FileManager()
{}

Scene FileManager::loadScene(QString filename)
{
    QDomDocument doc("SceneRayTracing");
    QFile file( filename.toStdString().data());

    if(!file.open(QIODevice::ReadOnly)) return Scene();
    if(!doc.setContent(&file))
    {
        file.close();
        return Scene();
    }

    file.close();

    QDomElement root = doc.documentElement();
    if(root.tagName() != "Scene") return Scene();
    Scene scene = Scene();

    QDomNode next = root.firstChild();
    while (!next.isNull()) {
        QDomElement element = next.toElement();

        if (!element.isNull()) {
            if (element.tagName() == "Camera") {
                Camera camera = Camera();

                QDomElement origin = element.firstChildElement("Eye").toElement();
                QDomElement lookAt = element.firstChildElement("At").toElement();
                QDomElement vup = element.firstChildElement("Up").toElement();

                camera.setOrigin(Vec4(origin.attribute("x","").toDouble(),
                                      origin.attribute("y","").toDouble(),
                                      origin.attribute("z","").toDouble()));
                camera.setLookAt(Vec4(lookAt.attribute("x","").toDouble(),
                                      lookAt.attribute("y","").toDouble(),
                                      lookAt.attribute("z","").toDouble()));
                camera.setVup(Vec4(vup.attribute("x","").toDouble(),
                                   vup.attribute("y","").toDouble(),
                                   vup.attribute("z","").toDouble()));
                scene.setCamera(camera);
            }

            if (element.tagName() == "Objects") {
                QDomNode obj = element.firstChildElement("Object");
                while (!obj.isNull()) {
                    Object3D* object;

                    QDomNode e = obj;
                    QDomElement eObj = e.toElement();
                    QString type = eObj.attribute("Type","");
                    QString name = eObj.attribute("Name","");
                    QString texture = eObj.attribute("Texture","");

                    if (type == "OBJCUBE") {
                        object = new Box();
                    } else if (type == "OBJPLANE") {
                        object = new Plane();
                    } else if (type == "OBJCYLINDER") {
                        object = new Cylinder();
                    } else if (type == "OBJSPHERE") {
                        object = new Sphere();
                    }

                    object->setName(name);
                    object->setType(type);
                    if (texture != "") {
                        Texture objTexture = Texture(texture);
                        object->setTexture(objTexture);
                    }

                    QDomElement pos = eObj.firstChildElement("Position").toElement();
                    Vec4 position = Vec4();
                    position.setX(pos.attribute("x","").toDouble());
                    position.setY(pos.attribute("y","").toDouble());
                    position.setZ(pos.attribute("z","").toDouble());

                    QDomElement rot = eObj.firstChildElement("Rotate").toElement();
                    Vec4 rotate = Vec4();
                    rotate.setX(rot.attribute("x","").toDouble());
                    rotate.setY(rot.attribute("y","").toDouble());
                    rotate.setZ(rot.attribute("z","").toDouble());

                    QDomElement scl = eObj.firstChildElement("Scale").toElement();
                    Vec4 scale = Vec4();
                    scale.setX(scl.attribute("x","").toDouble());
                    scale.setY(scl.attribute("y","").toDouble());
                    scale.setZ(scl.attribute("z","").toDouble());

                    object->applyTranslate(position.getX(),position.getY(),position.getZ());
                    object->applyRotate(rotate.getX(),true,false,false);
                    object->applyRotate(rotate.getY(),false,true,false);
                    object->applyRotate(rotate.getZ(),false,false,true);
                    object->applyScale(scale.getX(),scale.getY(),scale.getZ());

                    QDomElement material = eObj.firstChildElement("Material").toElement();
                    double reflection, refraction, shininess, glossy;

                    reflection = material.attribute("Reflection","").toDouble();
                    refraction = material.attribute("Refraction","").toDouble();
                    shininess = material.attribute("Shininess","").toDouble();
                    glossy = material.attribute("GlossyReflection","").toDouble();

                    QDomElement amb = material.firstChildElement("Ambient").toElement();
                    QDomElement spc = material.firstChildElement("Specular").toElement();
                    QDomElement dif = material.firstChildElement("Diffuse").toElement();

                    Material mat = Material(Color(amb.attribute("r","").toDouble(),
                                                  amb.attribute("g","").toDouble(),
                                                  amb.attribute("b","").toDouble()),
                                            Color(dif.attribute("r","").toDouble(),
                                                  dif.attribute("g","").toDouble(),
                                                  dif.attribute("b","").toDouble()),
                                            Color(spc.attribute("r","").toDouble(),
                                                  spc.attribute("g","").toDouble(),
                                                  spc.attribute("b","").toDouble()),
                                            shininess,refraction,reflection);
                    mat.setGlossy(glossy);
                    //if (refraction > 0) mat.setDissolve(0.1);

                    object->setMaterial(mat);
                    scene.addObject(object);
                    obj = obj.nextSibling();
                }
            }

            if (element.tagName() == "Lights") {
                QDomNode lgt = element.firstChildElement("Light");
                while(!lgt.isNull()) {
                    Light *light;

                    QDomNode e = lgt;
                    QDomElement eLgt = e.toElement();
                    QString type = eLgt.attribute("Type","");
                    QString name = eLgt.attribute("Name","");

                    if (type == "LIGHT_AMBIENT") {
                        light = new Light();

                        QDomElement material = eLgt.firstChildElement("Material").toElement();

                        QDomElement amb = material.firstChildElement("Ambient").toElement();
                        QDomElement spc = material.firstChildElement("Specular").toElement();
                        QDomElement dif = material.firstChildElement("Diffuse").toElement();

                        Material mat = Material(Color(amb.attribute("r","").toDouble(),
                                                      amb.attribute("g","").toDouble(),
                                                      amb.attribute("b","").toDouble()),
                                                Color(dif.attribute("r","").toDouble(),
                                                      dif.attribute("g","").toDouble(),
                                                      dif.attribute("b","").toDouble()),
                                                Color(spc.attribute("r","").toDouble(),
                                                      spc.attribute("g","").toDouble(),
                                                      spc.attribute("b","").toDouble()));

                        light->setMaterial(mat);
                        scene.setAmbientLight(light);
                    } else {
                        light = new Light();
                        QDomElement position = eLgt.firstChildElement("Position").toElement();
                        light->applyTranslate(position.attribute("x","").toDouble(),
                                              position.attribute("y","").toDouble(),
                                              position.attribute("z","").toDouble());

                        QDomElement material = eLgt.firstChildElement("Material").toElement();

                        QDomElement amb = material.firstChildElement("Ambient").toElement();
                        QDomElement spc = material.firstChildElement("Specular").toElement();
                        QDomElement dif = material.firstChildElement("Diffuse").toElement();

                        Material mat = Material(Color(amb.attribute("r","").toDouble(),
                                                      amb.attribute("g","").toDouble(),
                                                      amb.attribute("b","").toDouble()),
                                                Color(dif.attribute("r","").toDouble(),
                                                      dif.attribute("g","").toDouble(),
                                                      dif.attribute("b","").toDouble()),
                                                Color(spc.attribute("r","").toDouble(),
                                                      spc.attribute("g","").toDouble(),
                                                      spc.attribute("b","").toDouble()));
                        light->setType(type);

                        light->setMaterial(mat);
                        scene.addLight(light);
                    }
                    lgt = lgt.nextSibling();
                }
            }
        }
        next = next.nextSibling();
    }

    return scene;
}

bool FileManager::saveScene(QString filename, Scene scene)
{
    QDomDocument doc("SceneRayTracing");
    QDomElement root = doc.createElement("Scene");
    doc.appendChild(root);

    QDomElement camera = doc.createElement("Camera");
    QDomElement eye = doc.createElement("Eye");
    QDomElement at = doc.createElement("At");
    QDomElement up = doc.createElement("Up");

    eye.setAttribute("x",scene.getCamera().getOrigin().getX());
    eye.setAttribute("y",scene.getCamera().getOrigin().getY());
    eye.setAttribute("z",scene.getCamera().getOrigin().getZ());

    at.setAttribute("x",scene.getCamera().getLookAt().getX());
    at.setAttribute("y",scene.getCamera().getLookAt().getY());
    at.setAttribute("z",scene.getCamera().getLookAt().getZ());

    up.setAttribute("x",scene.getCamera().getVup().getX());
    up.setAttribute("y",scene.getCamera().getVup().getY());
    up.setAttribute("z",scene.getCamera().getVup().getZ());

    camera.appendChild(eye);
    camera.appendChild(at);
    camera.appendChild(up);

    QDomElement objects = doc.createElement("Objects");
    for (unsigned int i = 0; i < scene.objNum(); i++) {
        Object3D *object = scene.getObjAt(i);

        QDomElement obj = doc.createElement("Object");
        obj.setAttribute("Name",object->getName());
        obj.setAttribute("Type",object->getType());
        obj.setAttribute("Texture",object->getTexture().getName());

        QDomElement pos = doc.createElement("Position");
        pos.setAttribute("x",object->getOrigin().getX());
        pos.setAttribute("y",object->getOrigin().getY());
        pos.setAttribute("z",object->getOrigin().getZ());

        QDomElement rot = doc.createElement("Rotate");
        rot.setAttribute("x",object->getRot().getX());
        rot.setAttribute("y",object->getRot().getY());
        rot.setAttribute("z",object->getRot().getZ());

        QDomElement scl = doc.createElement("Scale");
        scl.setAttribute("x",object->getScale().getX());
        scl.setAttribute("y",object->getScale().getY());
        scl.setAttribute("z",object->getScale().getZ());

        QDomElement material = doc.createElement("Material");
        material.setAttribute("Reflection",object->getMaterial().getReflect());
        material.setAttribute("Refraction",object->getMaterial().getIor());
        material.setAttribute("Shininess",object->getMaterial().getShininess());
        material.setAttribute("GlossyReflection",object->getMaterial().getGlossy());
        QDomElement ambient = doc.createElement("Ambient");
        ambient.setAttribute("r",object->getMaterial().getAmbient().getRed());
        ambient.setAttribute("g",object->getMaterial().getAmbient().getGreen());
        ambient.setAttribute("b",object->getMaterial().getAmbient().getBlue());
        QDomElement specular = doc.createElement("Specular");
        specular.setAttribute("r",object->getMaterial().getSpecular().getRed());
        specular.setAttribute("g",object->getMaterial().getSpecular().getGreen());
        specular.setAttribute("b",object->getMaterial().getSpecular().getBlue());
        QDomElement diffuse = doc.createElement("Diffuse");
        diffuse.setAttribute("r",object->getMaterial().getDiffuse().getRed());
        diffuse.setAttribute("g",object->getMaterial().getDiffuse().getGreen());
        diffuse.setAttribute("b",object->getMaterial().getDiffuse().getBlue());

        material.appendChild(ambient);
        material.appendChild(specular);
        material.appendChild(diffuse);

        obj.appendChild(pos);
        obj.appendChild(rot);
        obj.appendChild(scl);
        obj.appendChild(material);

        objects.appendChild(obj);
    }

    QDomElement lights = doc.createElement("Lights");
    Light *light = scene.getAmbientLight();

    QDomElement lgt = doc.createElement("Light");
    lgt.setAttribute("Name",light->getName());
    lgt.setAttribute("Type",light->getType());

    QDomElement material = doc.createElement("Material");
    QDomElement ambient = doc.createElement("Ambient");
    ambient.setAttribute("r",light->getMaterial().getAmbient().getRed());
    ambient.setAttribute("g",light->getMaterial().getAmbient().getGreen());
    ambient.setAttribute("b",light->getMaterial().getAmbient().getBlue());
    QDomElement specular = doc.createElement("Specular");
    specular.setAttribute("r",light->getMaterial().getSpecular().getRed());
    specular.setAttribute("g",light->getMaterial().getSpecular().getGreen());
    specular.setAttribute("b",light->getMaterial().getSpecular().getBlue());
    QDomElement diffuse = doc.createElement("Diffuse");
    diffuse.setAttribute("r",light->getMaterial().getDiffuse().getRed());
    diffuse.setAttribute("g",light->getMaterial().getDiffuse().getGreen());
    diffuse.setAttribute("b",light->getMaterial().getDiffuse().getBlue());

    material.appendChild(ambient);
    material.appendChild(specular);
    material.appendChild(diffuse);

    lgt.appendChild(material);

    lights.appendChild(lgt);

    for (unsigned int i = 0; i < scene.lightNum(); i++) {
        light = scene.getLightAt(i);

        QDomElement lgt = doc.createElement("Light");
        lgt.setAttribute("Name",light->getName());
        lgt.setAttribute("Type",light->getType());

        QDomElement pos = doc.createElement("Position");
        pos.setAttribute("x",light->getOrigin().getX());
        pos.setAttribute("y",light->getOrigin().getY());
        pos.setAttribute("z",light->getOrigin().getZ());
        lgt.appendChild(pos);

        QDomElement material = doc.createElement("Material");
        QDomElement ambient = doc.createElement("Ambient");
        ambient.setAttribute("r",light->getMaterial().getAmbient().getRed());
        ambient.setAttribute("g",light->getMaterial().getAmbient().getGreen());
        ambient.setAttribute("b",light->getMaterial().getAmbient().getBlue());
        QDomElement specular = doc.createElement("Specular");
        specular.setAttribute("r",light->getMaterial().getSpecular().getRed());
        specular.setAttribute("g",light->getMaterial().getSpecular().getGreen());
        specular.setAttribute("b",light->getMaterial().getSpecular().getBlue());
        QDomElement diffuse = doc.createElement("Diffuse");
        diffuse.setAttribute("r",light->getMaterial().getDiffuse().getRed());
        diffuse.setAttribute("g",light->getMaterial().getDiffuse().getGreen());
        diffuse.setAttribute("b",light->getMaterial().getDiffuse().getBlue());

        material.appendChild(ambient);
        material.appendChild(specular);
        material.appendChild(diffuse);

        lgt.appendChild(pos);
        lgt.appendChild(material);

        lights.appendChild(lgt);
    }

    root.appendChild(camera);
    root.appendChild(objects);
    root.appendChild(lights);

    QString f = filename.toStdString().data();
    ofstream ff((f+".xml").toLocal8Bit().data());
    ff << doc.toString().toLocal8Bit().data();
    return true;
}
