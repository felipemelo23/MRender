#include <Render/render.h>
#include <Render/scene.h>
#include <sstream>
#include <QFileInfo>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <limits>

#include <QString>

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class FileManager
{
public:
    FileManager();

    Scene loadScene(QString filename);
    bool saveScene(QString filename, Scene scene);

};

#endif // FILEMANAGER_H
