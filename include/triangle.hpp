#pragma once
#include "screen.hpp"
#include "edge.hpp"
#include "pixel.hpp"
class Triangle
{
public:
    Triangle(Screen* s, Pixel* c, int x1, int y1, int x2, int y2, int x3, int y3);
    void draw();

    Edge edges[3];
    Screen* screen;
    int long_edge, short_edge1, short_edge2;

    Pixel color;
};
