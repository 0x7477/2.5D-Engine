#pragma once

#include "texture.hpp"
class Tile
{
public:
    Tile() {transparent = true;}
    Tile(bool t) {transparent = t; walkable = t;}

    bool isTransparent() {return transparent;}
    bool isWalkable() {return walkable;}

    bool transparent;
    bool walkable;
    Texture* texture;
};
