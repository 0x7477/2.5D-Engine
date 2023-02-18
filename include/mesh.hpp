#pragma once
#include <vector>
#include <string>
#include "triangle.hpp"
#include "game.hpp"
#include "worldpoint.hpp"
#include "quaternion.hpp"

/// @brief A Mesh displayable in the game
class Mesh
{

public:
    Mesh(Game *game, std::vector<Pixel> colors, const WorldPoint &pos,const Quaternion& rot, double scale, std::vector<WorldPoint> vertices);
    Mesh(Game *game, std::string path,std::vector<Pixel> colors, const WorldPoint &pos,const Quaternion& rot, double scale);
    /// @brief draw the Mesh
    void draw() const;
    Game *game;
    WorldPoint pos;
    Quaternion rot;
    double scale;
    std::vector<Pixel> colors;
    std::vector<WorldPoint> vertices;
};