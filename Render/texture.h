#include <QImage>
#include "color.h"
#include <QRgb>
#include <QColor>

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
    Texture();
    Texture(QString image);

    QImage getImage();
    void setImage(QImage &value);

    Color getColorAt(double x, double y); //x e y entre 0 e 1;

    QString getName();

private:
    QImage image;
    QString name;
};

#endif // TEXTURE_H
