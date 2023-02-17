#pragma once
#include <vector>
#include "triangle.hpp"
#include "game.hpp"
#include "worldpoint.hpp"
#include "quaternion.hpp"

/// @brief A Mesh displayable in the game
class Mesh
{

public:
    Mesh(Game* game, std::vector<Pixel> colors, const WorldPoint& pos,Quaternion rot,  double scale, std::vector<WorldPoint> vertices);
    /// @brief draw the Mesh
    void draw() const;

    Game* game;
    WorldPoint pos;
    Quaternion rot;
    double scale;
    std::vector<Pixel> colors;
    std::vector<WorldPoint> vertices;
};