#pragma once
#include <vector>
#include <string>
#include "triangle.hpp"
#include "game.hpp"
#include "worldpoint.hpp"
#include "quaternion.hpp"
#include "transform.hpp"

/// @brief A Mesh displayable in the game
class Mesh
{

public:
    Mesh(Game *game, std::vector<Pixel> colors, const Transform& transform, std::vector<WorldPoint> vertices);
    Mesh(Game *game, std::string path,std::vector<Pixel> colors, const Transform& transform);
    /// @brief draw the Mesh
    void draw() const;
    Game *game;
    Transform transform;
    std::vector<Pixel> colors;
    std::vector<WorldPoint> vertices;
};