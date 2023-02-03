#pragma once
#include "player.hpp"
#include "map.hpp"

/// @brief A raycast utility for the renderer
class Raycast
{
public:
    /// @brief get the distance to the Wall 
    /// @param player The player the rays are cast from
    /// @param map The map the rays should be cast on
    /// @param ray_angle the angle the ray should be cast
    /// @param ray_x the rays hit x pos
    /// @param ray_y the rays hit y pos
    /// @return the distance traversed
    static double raycast(Player*player, Map* map, double ray_angle, double* ray_x, double* ray_y);
private:
    
    /// @brief Advance the Ray to the next Tile
    /// @param pos_x The rays next x pos
    /// @param pos_y The rays next y pos
    /// @param angle The rays angle
    /// @return the distance traveled
    static double getNearestHit(double *pos_x, double *pos_y, double angle);

};