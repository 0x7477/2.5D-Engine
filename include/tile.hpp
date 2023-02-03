#pragma once

#include "texture.hpp"

/// @brief A tile inside a map
class Tile
{
public:
    /// @brief create a transparent, walkable Tile
    Tile() {transparent = true;walkable = true;}
    
    /// @brief Creates a tile
    /// @param t set if the tile is walkable and invisible or not
    Tile(bool t) {transparent = t; walkable = t;}

    /// @brief check if tile is transparent
    /// @return returns the transparency of the tile
    bool isTransparent() {return transparent;}
    /// @brief check if tile is walkable
    /// @return returns the walkability of the tile
    bool isWalkable() {return walkable;}

    bool transparent;
    bool walkable;
    Texture* texture;
};
