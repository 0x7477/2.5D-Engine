#pragma once
#include "texture.hpp"
#include "point.hpp"
#include <string>

class Player;

class Billboard
{
public:
    /// @brief creates a Billboard
    /// @param pos  the position
    /// @param texture the textures name
    /// @param width width in world size
    /// @param height height in world size
    Billboard(WorldPoint pos, std::string texture, double width =1, double height = 1);

    bool isVisible(Player* player) const;
    double getAngle(Player* player) const;
    WorldPoint pos;
    double width,height;
    Texture* texture;
};