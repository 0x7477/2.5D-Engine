#pragma once

#include <cmath>
#include "world_point.hpp"

class WorldPoint;
class Map;

/// @brief The Player object
class Player
{
public:
    Player();
    /// @brief Moves the player via input
    /// @param map the map the player moves through
    /// @param deltaTime the time passed since last move
    void move(Map* map, double deltaTime);

    /// @brief checks if a point is visible by the player
    /// @param point the point to check if it is visible
    /// @return returns if the point is visible
    bool isPointVisible(const WorldPoint& point) const;
    bool isNormalVisible(const WorldPoint& point) const;

    //The players position
    double pos_x=17.8162, pos_y=7.85383, pos_z;
    //The players rotation
    double angle = 4.71854;
    //The players field of view
    double field_of_view = 100 * M_PI / 360.0;

    WorldPoint view_l, view_r;
    //the turn and movement speed
    double turn_speed = 0.000003;
    double movement_speed = 0.00001;
};