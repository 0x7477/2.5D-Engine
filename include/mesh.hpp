#pragma once
#include <vector>
#include <string>
#include "triangle.hpp"
#include "game.hpp"
#include "world_point.hpp"
#include "quaternion.hpp"
#include "transform.hpp"
#include "texture.hpp"
#include "face.hpp"
#include "obj/obj.hpp"

/// @brief A Mesh displayable in the game
class Mesh
{

public:
    Mesh(Game *game, std::string path, const Transform& transform);
    /// @brief draw the Mesh
    void draw();
    Game *game;
    Transform transform;
    Texture* texture;

    std::vector<WorldPoint> world_points;
    std::vector<ScreenPoint> screen_points;
    std::vector<UVPoint> uv_points;

    OBJ::OBJ obj;
};