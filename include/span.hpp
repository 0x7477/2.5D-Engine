#pragma once
#include "pixel.hpp"
#include "triangle.hpp"
class Span
{
public:
    Span(Triangle* t, int x1_, float z1_, int x2_, float z2_);

    int x1, x2;
    float depth1, depth2;
    Triangle* t;

    int getLength();
    void draw(int y);

};