
#include "texture.h"

Texture::Texture(){}

Texture::Texture(QString image)
{
    this->name = image;
    this->image = QImage(image);
}
QImage Texture::getImage()
{
    return image;
}

void Texture::setImage(QImage &value)
{
    image = value;
}

Color Texture::getColorAt(double x, double y)
{
    int u = x*image.width();
    int v = y*image.height();

    QColor color = QColor(image.pixel(u,v));

    return Color(color.redF(), color.greenF(), color.blueF());
}
QString Texture::getName()
{
    return name;
}


