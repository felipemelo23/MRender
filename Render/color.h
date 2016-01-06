#include "Math/vec4.h"

#ifndef COLOR_H
#define COLOR_H

class Color : public Vec4
{
public:
    Color();
    Color(double red, double green, double blue);

    double getRed();
    void setRed(double value);

    double getGreen();
    void setGreen(double value);

    double getBlue();
    void setBlue(double value);

    Color operator + (Color c);
    Color operator - (Color c);
    Color operator * (double d);
    Color operator * (Color c);
    Color operator / (double d);
};

#endif // COLOR_H
