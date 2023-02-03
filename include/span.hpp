#pragma once
#include "pixel.hpp"
#include "triangle.hpp"

/// @brief An edges span
class Span
{
public:
    Span(Triangle* t, int x1_, float z1_, int x2_, float z2_);

    /// @brief get the length of the span
    /// @return the legth of the span in pixelspace
    int getLength();

    /// @brief draws the spin at y choord y
    /// @param y the choord y to be drawn at
    void draw(int y);


    int x1, x2;
    float depth1, depth2;
    Triangle* t;


};