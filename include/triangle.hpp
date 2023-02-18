#pragma once
#include "screen.hpp"
#include "edge.hpp"
#include "pixel.hpp"
#include "worldpoint.hpp"

/// @brief A screenspace triangle
class Triangle
{
public:
    /// @brief creates a Tringle
    /// @param screen the screen in which the triangle should be drawn at
    /// @param color the color f the triangle
    /// @param p1 point one
    /// @param p2 point two
    /// @param p3 point three
    Triangle(Game* game, Pixel color, const WorldPoint& p1, const WorldPoint& p2, const WorldPoint& p3);
    /// @brief draws the tringle at the screen
    void draw();

    
    Edge edges[3];
    Screen* screen;
    int long_edge, short_edge1, short_edge2;
    Pixel color;
};
