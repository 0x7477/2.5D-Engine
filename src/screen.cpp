#include "screen.hpp"
#include "colors.hpp"

Screen::Screen(std::size_t width, std::size_t height)
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
void Screen::setColor(std::size_t x, std::size_t y, Pixel color)
{
    buffer[x+ y*width] = color;
}

void Screen::setDepth(std::size_t x, std::size_t y, float depth)
{
    depthmap[x+ y*width] = depth;
}

float Screen::getDepth(std::size_t x, std::size_t y)
{
    if(x < 0 || x >= width || y < 0 || y >= height) 
        std::cout << x << y << "\n";
    return depthmap[x+ y*width];
}

void Screen::fillZBuffer(float depth)
{
    for(std::size_t i = 0; i < width*height; i++)
        depthmap[i] = depth;
}



void Screen::fill(Pixel color)
{
    for(std::size_t i = 0; i < width*height; i++)
        buffer[i] = color;
}

