#pragma once
#include "tile.hpp"

class Game;

class Map
{
    public:
    Map(int width, int height);
    ~Map();
    Map(const Map&) = delete;
    Map(Map&& other) = delete;
    Map& operator=(const Map&) = delete;
    Map& operator=(Map&& other) = delete;

    Tile* operator()(int x, int y);

    void generate(Game* game);
    void display();

    bool covers(double x, double y);

    const int width = 50, height = 50;
    Tile* map;
};
