#include "player.hpp"
#include "window_manager.hpp"
#include "map.hpp"
void Player::move(Map* map, double deltaTime)
{

    double new_pos_x = pos_x, new_pos_y = pos_y;
    auto forward = sin(angle) * deltaTime * movement_speed;
    auto left = cos(angle) * deltaTime * movement_speed;
    if (WindowManager::buttons['a'])
        angle -= turn_speed * deltaTime;
    if (WindowManager::buttons['d'])
        angle += turn_speed * deltaTime;
    if (WindowManager::buttons['w'])
    {
        new_pos_x += forward;
        new_pos_y += left;
    }
    if (WindowManager::buttons['s'])
    {
        new_pos_x -= forward;
        new_pos_y -= left;
    }

    if((*map)((int)new_pos_x,(int)new_pos_y)->isWalkable()) 
    {
        pos_x = new_pos_x;
        pos_y = new_pos_y;
    }
}

Player::Player()
{
}