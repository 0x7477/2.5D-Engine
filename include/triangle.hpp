#pragma once
#include "screen.hpp"
#include "edge.hpp"
#include "texture.hpp"
#include "world_point.hpp"

class Mesh;

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
    Triangle(Mesh* mesh, int p[3], int uv[3]);
    /// @brief draws the triangle at the screen
    void draw();

    
    Edge edges[3];
    Screen* screen;
    int long_edge, short_edge1, short_edge2;
    Texture* texture;
};
