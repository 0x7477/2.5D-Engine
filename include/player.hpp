#pragma once

#include <cmath>
#include "map.hpp"

class WorldPoint;

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
    bool isVisible(const WorldPoint& point) const;

    //The players position
    double pos_x= 2.4, pos_y= 6.5, pos_z;
    //The players rotation
    double angle = M_PI - 1;
    //The players field of view
    double field_of_view = 100 * M_PI / 360.0;

    //the turn and movement speed
    double turn_speed = 0.000003;
    double movement_speed = 0.00001;
};