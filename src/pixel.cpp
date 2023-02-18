#include "pixel.hpp"

Pixel::Pixel()
{
    r = 0;
    g = 0;
    b = 0;
    a = 255;
}

Pixel::Pixel(int rgba)
{
    r = (rgba & 0xFF0000) >> 16;
    g = (rgba & 0xFF00) >> 8;
    b = (rgba & 0xFF);
    a = 255;
}

void Pixel::setBrightness(float brightness)
{
    r = (unsigned char)((float)r * brightness);
    g = (unsigned char)((float)g * brightness);
    b = (unsigned char)((float)b * brightness);
}

std::ostream &operator<<(std::ostream &os, const Pixel &p)
{
    return os << "(" << (int)p.r << "," << (int)p.g << "," << (int)p.b << "," << (int)p.a << ")";
}