#pragma once
#include "player.hpp"
#include "map.hpp"


class Raycast
{
public:
    static double raycast(Player*player, Map* map, double ray_angle, double* ray_x, double* ray_y);
private:
    static double getNearestHit(double *pos_x, double * pos_y, double angle);

};