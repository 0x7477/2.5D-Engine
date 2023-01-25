#pragma once
#include "pixel.hpp"
#include "triangle.hpp"
class Span
{
public:
    Span(Triangle* t, int x1, int x2);

    int x1, x2;
    Triangle* t;

    int getLength();
    void draw(int y);
};