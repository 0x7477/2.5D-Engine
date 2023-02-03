#pragma once

#include <cmath>
#include "map.hpp"

class WorldPoint;

class Player
{
public:
    Player();
    void move(Map* map, double deltaTime);

    bool isVisible(const WorldPoint& point) const;
    double pos_x= 2.4, pos_y= 6.5, pos_z;
    double angle = M_PI - 1;
    double field_of_view = 100 * M_PI / 360.0;

    double turn_speed = 0.000003;
    double movement_speed = 0.00001;

    double height_factor = 0.3;
};