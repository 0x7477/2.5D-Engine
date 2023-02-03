#include "map.hpp"
#include "game.hpp"
#include <cstdlib>
#include <iostream>
Map::Map(int width, int height)
:width{width},height{height}
{
    map = new Tile[width*height];
}

Map::~Map()
{
    delete[] map;
}


Tile* Map::operator()(int x, int y)
{
    return &map[x + y*width];
}

void Map::generate()
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            // set transparancy randomly (3% chance)
            map[x + y * width].transparent = !(x % (width - 1) == 0 || y % (height - 1) == 0 || rand() % 100 <3);
            map[x + y * width].walkable = map[x + y * width].transparent;

            //apply the twi textures in a checkboard pattern 
            map[x + y * width].texture = &(Game::textures[((x+y)%2==0)?"wall":"wall2"]);
        }
    }
}

void Map::display()
{
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
            std::cout << (map[x + y * width].transparent?" ":"#");
        
        std::cout << "\n";
    }
}


bool Map::covers(double x, double y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}
