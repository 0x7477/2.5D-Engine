#include "screen.hpp"
#include "colors.hpp"

Screen::Screen(int width, int height)
:width{width},height{height}
{
    buffer = new Pixel[width*height];
    depthmap = new float[width*height];
}

Screen::~Screen()
{
    delete[] buffer;
    delete[] depthmap;
}
void Screen::setColor(int x, int y, Pixel color)
{
    buffer[x+ y*width] = color;
}

void Screen::setDepth(int x, int y, float depth)
{
    depthmap[x+ y*width] = depth;
}

float Screen::getDepth(int x, int y)
{
    return depthmap[x+ y*width];
}

void Screen::fillZBuffer(float depth)
{
    for(int i = 0; i < width*height; i++)
        depthmap[i] = depth;
}



void Screen::fill(Pixel color)
{
    for(int i = 0; i < width*height; i++)
        buffer[i] = color;
}

