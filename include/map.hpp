#pragma once
#include "tile.hpp"

class Game;

class Map
{
    public:
    /// @brief Creates a new Map
    /// @param width with of the Map
    /// @param height height of the Map
    Map(int width, int height);
    ~Map();
    Map(const Map&) = delete;
    Map(Map&& other) = delete;
    Map& operator=(const Map&) = delete;
    Map& operator=(Map&& other) = delete;

    /// @brief Gets the Tile at given position
    /// @param x the x position
    /// @param y the y position
    /// @return the tile at x,y
    Tile* operator()(int x, int y);

    /// @brief Generates a Map
    void generate();
    /// @brief displays the map in the terminal
    void display();

    /// @brief Checks if the Coordinates are inside the map
    /// @param x the x pos
    /// @param y the y pos
    /// @return if the Coordinates are in the map
    bool covers(double x, double y);

    const int width = 50, height = 50;
    Tile* map;
};
