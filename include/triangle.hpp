#pragma once
#include "screen.hpp"
#include "edge.hpp"
#include "pixel.hpp"
#include "point.hpp"
class Triangle
{
public:
    Triangle(Screen* s, Pixel c, const ScreenPoint& p1, const ScreenPoint& p2, const ScreenPoint& p3);
    void draw();

    Edge edges[3];
    Screen* screen;
    int long_edge, short_edge1, short_edge2;

    Pixel color;
};
