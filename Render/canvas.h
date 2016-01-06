#include "color.h"

#ifndef CANVAS_H
#define CANVAS_H

class Canvas
{
public:
    Canvas();
    Canvas(int height, int width);

    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);

    Color getPixel(int i, int j);
    void setPixel(int i, int j, Color c);

private:
    int height;
    int width;
    Color **pixels;

    void allocateCanvas();
};

#endif // CANVAS_H
