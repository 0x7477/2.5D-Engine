#pragma once

#include <cmath>
#include "map.hpp"


class Player
{
public:
    Player();
    void move(Map* map, double deltaTime);
    double pos_x= 2.4, pos_y= 6.5, pos_z;
    double angle = M_PI - 1;
    double field_of_view = 100 * M_PI / 360.0;

    double turn_speed = 0.000001;
    double movement_speed = 0.00001;

    double height_factor = 0.3;
};