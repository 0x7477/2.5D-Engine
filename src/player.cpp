#include "player.hpp"
#include "window_manager.hpp"
#include "map.hpp"
#include "world_point.hpp"

bool Player::isVisible(const WorldPoint& point) const
{
    double angle = point.getAngle(this);
    return fabs(angle) < field_of_view / 2;
}

void Player::move(Map* map, double deltaTime)
{
    double new_pos_x = pos_x, new_pos_y = pos_y;

    //calculate steps to forward and left
    auto forward = sin(angle) * deltaTime * movement_speed;
    auto left = cos(angle) * deltaTime * movement_speed;

    //move the player
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

    //if new pos is walkable update the position
    if((*map)((int)new_pos_x,(int)new_pos_y)->isWalkable()) 
    {
        pos_x = new_pos_x;
        pos_y = new_pos_y;
    }

    view = {sin(angle),cos(angle),0};
}

Player::Player(){}