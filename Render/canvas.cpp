#include "canvas.h"

Canvas::Canvas()
{
    height = 480;
    width = 480;
    allocateCanvas();
}

Canvas::Canvas(int height, int width)
{
    this->height = height;
    this->width = width;
    allocateCanvas();
}

int Canvas::getHeight() const
{
    return height;
}

void Canvas::setHeight(int value)
{
    height = value;
}
int Canvas::getWidth() const
{
    return width;
}

void Canvas::setWidth(int value)
{
    width = value;
}

Color Canvas::getPixel(int i, int j)
{
    return pixels[i][j];
}

void Canvas::setPixel(int i, int j, Color c)
{
    pixels[i][j] = c;
}

void Canvas::allocateCanvas()
{
    pixels = new Color*[width];
    for (unsigned int i = 0; i < width; i++) {
        pixels[i] = new Color[height];
    }
}


