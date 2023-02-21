#pragma once
#include "tile.hpp"

class Game;

/// @brief The Map of the game
class Map
{
    public:
    /// @brief Creates a new Map
    /// @param width with of the Map
    /// @param height height of the Map
    Map(std::size_t width, std::size_t height);
    ~Map();
    Map(const Map&) = delete;
    Map(Map&& other) = delete;
    Map& operator=(const Map&) = delete;
    Map& operator=(Map&& other) = delete;

    /// @brief Gets the Tile at given position
    /// @param x the x position
    /// @param y the y position
    /// @return the tile at x,y
    Tile* operator()(std::size_t x, std::size_t y);

    /// @brief Generates a Map
    void generate();
    /// @brief displays the map in the terminal
    void display();

    /// @brief Checks if the Coordinates are inside the map
    /// @param x the x pos
    /// @param y the y pos
    /// @return if the Coordinates are in the map
    bool covers(double x, double y);

    const std::size_t width = 50, height = 50;
    Tile* map;
};
