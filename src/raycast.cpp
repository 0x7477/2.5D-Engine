#include "raycast.hpp"
#include <iostream>
double Raycast::raycast(Player *player, Map *map, double ray_angle, double* ray_x, double* ray_y)
{
    double distance = 0;
    *ray_x = player->pos_x;
    *ray_y = player->pos_y;

    double deltaDistance = 0.0000000000001f;

    double delta_x = sin(ray_angle) * deltaDistance;
    double delta_y = cos(ray_angle) * deltaDistance;
    while (map->covers(*ray_x,*ray_y) && (*map)((int)(*ray_x + delta_x),(int)(*ray_y +delta_y))->isTransparent())
        distance += getNearestHit(ray_x, ray_y, ray_angle);
    
    *ray_x += delta_x;
    *ray_y += delta_y;
    return distance;
}

double Raycast::getNearestHit(double *pos_x, double *pos_y, double angle)
{
    double rel_px = fmod(*pos_x, 1);
    double rel_py = fmod(*pos_y, 1);

    double ray_x = sin(angle);
    double ray_y = cos(angle);

    double distances[6];
    // When is it going to hit x = 1
    // 1=rel_px + r* ray_x
    //(1-rel_px/ray_x)  = r

    

    distances[0] = (((1 - rel_px) / ray_x));
    distances[1] = (((0 - rel_px) / ray_x));
    distances[2] = (((-1 - rel_px) / ray_x));
    distances[3] = (((1 - rel_py) / ray_y));
    distances[4] = (((0 - rel_py) / ray_y));
    distances[5] = (((-1 - rel_py) / ray_y));

    double smallest = __DBL_MAX__;

    for (int i = 0; i < 6; i++)
    {
        if(distances[i] <= 0) continue;

        smallest = std::min(smallest, distances[i]);
    }

    *pos_x += smallest * ray_x;
    *pos_y += smallest * ray_y;

    return smallest;
}
