#include "color.h"

Color::Color() : Vec4(0,0,0,Vec4().VECTOR) { }

Color::Color(double red, double green, double blue) : Vec4(red,green,blue) { }

double Color::getRed() {
    return this->x;
}

void Color::setRed(double value) {
    this->x = value;
}

double Color::getGreen() {
    return this->y;
}

void Color::setGreen(double value) {
    this->y = value;
}

double Color::getBlue() {
    return this->z;
}

void Color::setBlue(double value) {
    this->z = value;
}

Color Color::operator +(Color c)
{
    return Color(x+c.getX(), y+c.getY(), z+c.getZ());
}

Color Color::operator -(Color c)
{
    return Color(x-c.getX(), y-c.getY(), z-c.getZ());
}

Color Color::operator *(double d)
{
    return Color(d*x, d*y, d*z);
}

Color Color::operator *(Color c)
{
    return Color(x*c.getRed(), y*c.getGreen(), z*c.getBlue());
}

Color Color::operator /(double d)
{
    return Color(x/d, y/d, z/d);
}
