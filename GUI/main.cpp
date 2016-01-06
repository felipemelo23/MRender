#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <time.h>

#include "Math/vec4.h"
#include "Math/mtx4.h"
#include "filemanager.h"
#include "imagecreator.h"
#include <Render/canvas.h>
#include <Render/color.h>
#include <Render/material.h>
#include <Render/ray.h>
#include <Render/render.h>
#include <Render/scene.h>
#include <Objects/boundingbox.h>
#include <Objects/box.h>
#include <Objects/camera.h>
#include <Objects/cone.h>
#include <Objects/cylinder.h>
#include <Objects/light.h>
#include <Objects/object3d.h>
#include <Objects/plane.h>
#include <Objects/pontuallight.h>
#include <Objects/softlight.h>
#include <Objects/sphere.h>

using namespace std;

Scene createScene();

Material mtGeneric = Material(Color(1,1,1),Color(1,1,1),Color(1,1,1),3);
Material mtObsidian = Material(Color(0.05375,0.05,0.06625),Color(0.332741,0.328634,0.346435),Color(0.18275,0.17,0.22525),0.3,0,0.06);
Material mtGolden = Material(Color(0.3,0.2,0.2),Color(0.7,0.6,0.1),Color(0.8,0.7,0.6),5);
Material mtSilver = Material(Color(0.5,0.5,0.5),Color(0.6,0.6,0.6),Color(0.0,0.0,0.0),0);
Material mtMirror = Material(Color(0.4,0.4,0.4),Color(0.6,0.6,0.6),Color(0.7,0.7,0.7),5,0.0,0.8);
Material mtGlass = Material(Color(0.4,0.4,0.4),Color(0.6,0.6,0.6),Color(0.7,0.7,0.7),5,20,0.0,0.1);
Material mtRed = Material(Color(0.4,0.2,0.2),Color(0.6,0.2,0.2),Color(0.0,0.0,0.0),0);
Material mtGreen = Material(Color(0.1,0.3,0.1),Color(0.1,0.5,0.1),Color(0.0,0.0,0.0),0);
Material mtBlue = Material(Color(0.13,0.12,0.3),Color(0.13,0.12,0.5),Color(0.0,0.0,0.0),0);
Material mtRuby = Material(Color(0.1745,0.01175,0.01175),
                           Color(0.61424,0.04136,0.04136),
                           Color(0.727811,0.626959,0.626959),
                           0.88,20,0.2,0.9);

Texture txWood = Texture("wood.jpg");
Texture txDarkWood = Texture("dark_wood.jpg");
Texture txSteel = Texture("steel.jpg");
Texture txSteelBox = Texture("steel_box.jpg");
Texture tx1Ball = Texture("1ball.jpg");
Texture tx2Ball = Texture("2ball.jpg");
Texture tx3Ball = Texture("3ball.jpg");
Texture tx4Ball = Texture("4ball.jpg");
Texture tx5Ball = Texture("5ball.jpg");
Texture tx6Ball = Texture("6ball.jpg");
Texture tx7Ball = Texture("7ball.jpg");
Texture tx8Ball = Texture("8ball.jpg");
Texture txPokeball = Texture("pokeball.png");
Texture txGreatball("greatball.png");
Texture txUltraball("ultraball.png");
Texture txMasterball("masterball.png");
Texture txEarth = Texture("earth.png");
Texture txRedSteel = Texture("red_steel.jpg");
Texture txWoodFloor = Texture("wood_floor.jpg");
Texture txWall = Texture("wall_texture.jpg");
Texture txGreenVelvet("green_velvet.jpg");
Texture txImbuiaWood("imbuia_wood.jpg");
Texture txFold("fold.jpg");
Texture txSteelCylinder("steel_cylinder.jpg");
Texture txErondor("erondor.png");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Scene scene;
    Render render = Render();
    FileManager fileManager = FileManager();

    cout << "Loading Scene..." << endl;

    //USE ESSA FUNCAO PARA CARREGAR UMA CENA.
    scene = fileManager.loadScene("RedSteelBox.xml");

    //USE ESSA FUNCAO PARA CRIAR UMA CENA.
    //scene = createScene();

    //USE ESSA FUNCAO PARA SALVAR UMA CENA. (nao colocar a extensao no nome do arquivo)
    //fileManager.saveScene("Pokeballs",scene);

    cout << "Scene Loaded." << endl;

    /*DETERMINE A RESOLUÇÃO DA IMAGEM
      Baixa - 100
      Média - 200
      Alta - 400
      Muito Alta - 800
    */
    int screenSize = 300;

    //DETERMINE A COR DE BACKGROUND DA CENA
    render.setBackgroundColor(Color(0.1,0.1,0.2));

    //ESCOLHA USAR OU NÃO HIERARQUICAL BOUNDING BOX
    render.useBoundingBox(true);

    //DETERMINE A QUANTIDADE DE RAIO LANÇADOS POR PIXEL
    render.setSamples(4);

    //DETERMINE O DEPTH OF FIELD
    //render.setDepthOfField(15.0);

    //DETERMINE O NÍVEL DE SOFT SHADOWS (valores entre 0 e 1)
    //render.setSoftShadows(0.7);

    Canvas canvas = Canvas(scene.getCamera().getHeight()*screenSize,scene.getCamera().getWidth()*screenSize);
    render.setCanvas(canvas);
    render.setScene(scene);
    cout << "Rendering..." << endl;
    const clock_t begin_time = clock();
    render.renderScene();
    QString fileName = QString::number(render.getScene().objNum()) + " objects in ";
    fileName += QString::number(float( clock () - begin_time ) /  CLOCKS_PER_SEC) + " seconds";
    fileName += " " + QString::number(render.getCanvas().getWidth()) + "x" + QString::number(render.getCanvas().getHeight());
    if (render.getUseBoundingBox()) {
        fileName += " using HBB";
    } else {
        fileName += " not using HBB";
    }
    fileName += " with " + QString::number(render.getSamples()) + " samples";
    fileName += " " + QString::number(render.getSoftShadows()) + " soft shadows";
    fileName += " " + QString::number(render.getDepthOfField()) + " depth of field";
    cout << "Rendered in: " << fileName.toStdString() << endl;
    ImageCreator ic = ImageCreator(render.getCanvas(),fileName+".bmp");
    ic.createImage();
    ic.save();
    w.setImageLabel(ic.getImage());
    w.show();

    return a.exec();
}

//UTILIZE ESSA FUNÇÃO PARA CRIAR UMA CENA.
Scene createScene() {
    Scene scene = Scene();
    Camera camera = Camera();

    //SE O MATERIAL FOR REFLEXIVO, DETERMINE O GLOSSY REFLECTION (valores entre 0 e 1)
    //mtMirror.setGlossy(0.2);

    //CRIE OBJETOS
    Object3D *world = new Sphere(mtGeneric);

    //FAÇA TRANSFORMAÇÕES NOS OBJETOS.

    //COLOQUE TEXTURA NOS OBJETOS.
    world->setTexture(txErondor);

    //ADICIONE OBJETOS A CENA
    scene.addObject(world);

    //CRIE LUZES
    Light *aLight = new Light();
    Light* light = new PontualLight();

    //FAÇA TRANSAFORMAÇÕES NAS LUZES.
    light->applyTranslate(4,4,4);

    //ADICIONE LUZES A CENA
    scene.setAmbientLight(aLight);
    scene.addLight(light);

    //POSICIONE A CAMERA
    camera.setOrigin(Vec4(-3,0,0,1));
    camera.setWidth(1);
    camera.setHeight(1);
    scene.setCamera(camera);
    return scene;
}
