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