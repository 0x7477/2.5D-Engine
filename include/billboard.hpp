#pragma once
#include "texture.hpp"
#include "point.hpp"
#include <string>

class Player;

/// @brief A Billboard Object in the game
class Billboard
{
public:
    /// @brief creates a Billboard
    /// @param pos  the position
    /// @param texture the textures name
    /// @param width width in world size
    /// @param height height in world size
    Billboard(WorldPoint pos, std::string texture, double width =1, double height = 1);

    /// @brief checks if Object is visible
    /// @param player 
    /// @return returns if object is visible
    bool isVisible(Player* player) const;
    /// @brief get the Angle relative to the player
    /// @param player 
    /// @return returns the angle relatve to the player    
    double getAngle(Player* player) const;
        
    WorldPoint pos;
    double width,height;
    Texture* texture;
};