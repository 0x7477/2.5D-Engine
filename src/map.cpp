#include "map.hpp"
#include "game.hpp"
#include <cstdlib>
#include <iostream>
Map::Map(int width, int height)
    : width{width}, height{height}
{
    map = new Tile[width * height];
}

Map::~Map()
{
    delete[] map;
}

Tile *Map::operator()(int x, int y)
{
    return &map[x + y * width];
}

void Map::generate()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            // set transparancy randomly (3% chance)
            map[x + y * width].transparent = !(x % (width - 1) == 0 || y % (height - 1) == 0 || rand() % 100 < 0);
            map[x + y * width].walkable = map[x + y * width].transparent;
            map[x + y * width].ceiling_transparent = true;

            // apply the twi textures in a checkboard pattern
            map[x + y * width].texture = &(Game::textures["fence"]);
        }
    }

    for (int y = 10; y < 20; y++)
    {
        for (int x = 10; x < 20; x++)
        {
            map[x + y * width].ceiling_transparent = false;
            map[x + y * width].ceiling_texture = &(Game::textures["floor"]);
            map[x + y * width].floor_texture = &(Game::textures["floor"]);

            if (x > 10 && x < 19 && y > 10 && y < 19)
                continue;
            map[x + y * width].transparent = false;
            map[x + y * width].walkable = false;

            map[x + y * width].texture = &(Game::textures["wall"]);
        }
    }

    map[15 + 10 * width].transparent = true;
    map[15 + 10 * width].walkable = true;
}

void Map::display()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
            std::cout << (map[x + y * width].transparent ? " " : "#");

        std::cout << "\n";
    }
}

bool Map::covers(double x, double y)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}
