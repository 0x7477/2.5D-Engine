#pragma once
#include "pixel.hpp"
#include "triangle.hpp"
#include "uv_point.hpp"

/// @brief An edges span
class Span
{
public:
    Span(Triangle *t, int x1, float z1, int x2, float z2, const UVPoint &uv1, const UVPoint &uv2);

    /// @brief get the length of the span
    /// @return the legth of the span in pixelspace
    int getLength();

    /// @brief draws the spin at y choord y
    /// @param y the choord y to be drawn at
    void draw(int y);

    int x1, x2;
    float depth1, depth2;
    UVPoint uv1, uv2;
    Triangle *t;
};