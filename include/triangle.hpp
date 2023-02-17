#pragma once
#include "screen.hpp"
#include "edge.hpp"
#include "pixel.hpp"
#include "screenpoint.hpp"

/// @brief A screenspace triangle
class Triangle
{
public:
    /// @brief creates a Tringle
    /// @param screen the screen in which the triangle should be drawn at
    /// @param colorthe color f the triangle
    /// @param p1 point one
    /// @param p2 point two
    /// @param p3 point three
    Triangle(Screen* screen, Pixel color, const ScreenPoint& p1, const ScreenPoint& p2, const ScreenPoint& p3);
    /// @brief draws the tringle at the screen
    void draw();

    Edge edges[3];
    Screen* screen;
    int long_edge, short_edge1, short_edge2;
    Pixel color;
};
