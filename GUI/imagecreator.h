#include <QImage>
#include <Render/canvas.h>

#ifndef IMAGECREATOR_H
#define IMAGECREATOR_H

class ImageCreator
{
public:
    ImageCreator(Canvas canvas, QString name="image.bmp");

    void createImage();

    Canvas getCanvas();
    void setCanvas(Canvas &value);

    QString getName();
    void setName(QString &value);

    QImage getImage();

    void save();

private:
    bool created;
    Canvas canvas;
    QString name;
    QImage image;

    //Avoid Color Overflow
    double aCO(double c1);
};

#endif // IMAGECREATOR_H
