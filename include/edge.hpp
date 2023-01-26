#pragma once
#include "point.hpp"

class Triangle;

class Edge
{
public:
    Edge(Triangle* t, const ScreenPoint& p1, const ScreenPoint& p2);

    int getLength();
    int getWidth();
    ScreenPoint p1,p2;
    Triangle* t;
    void drawSpans(Edge edge2);
};
