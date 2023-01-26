#pragma once
#include "point.hpp"

class Triangle;

class Edge
{
public:
    Edge(Triangle* t, int x1, int y1, int x2, int y2);
    Edge(){};

    int getLength();
    int getWidth();
    int x1, y1, x2, y2;
    Triangle* t;
    void drawSpans(Edge edge2);
};
