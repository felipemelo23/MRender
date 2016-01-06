#include "imagecreator.h"

ImageCreator::ImageCreator(Canvas canvas, QString name)
{
    this->canvas = canvas;
    this->name = name;
    this->created = false;
}

Canvas ImageCreator::getCanvas()
{
    return canvas;
}

void ImageCreator::setCanvas(Canvas &value)
{
    canvas = value;
}

QString ImageCreator::getName()
{
    return name;
}

void ImageCreator::setName(QString &value)
{
    name = value;
}
QImage ImageCreator::getImage()
{
    if (created) return image;
    return QImage();
}

void ImageCreator::save()
{
    if (created) image.save(name);
}

void ImageCreator::createImage()
{
    image = QImage(canvas.getWidth(),canvas.getHeight(),QImage().Format_RGB32);

    for (unsigned int i = 0; i < canvas.getWidth(); i++) {
        for (unsigned int j = 0; j < canvas.getHeight(); j++) {
            image.setPixel(i,j,qRgb(255*aCO(canvas.getPixel(i,j).getRed()),
                                    255*aCO(canvas.getPixel(i,j).getGreen()),
                                    255*aCO(canvas.getPixel(i,j).getBlue())));
        }
    }

    created = true;
}

double ImageCreator::aCO(double c1) {
    if (c1 > 1) {
        return 1;
    } else if (c1 < 0) {
        return 0;
    } else {
        return c1;
    }
}


