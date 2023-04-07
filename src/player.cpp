#include "player.hpp"
#include "window_manager.hpp"
#include "map.hpp"
#include "world_point.hpp"

bool Player::isPointVisible(const WorldPoint& point) const
{
    double angle = point.getAngle(this);
    return fabs(angle) < field_of_view / 2;
}


bool Player::isNormalVisible(const WorldPoint& point) const
{
    WorldPoint player_angle = {sin(angle),cos(angle),0};

    
    return (player_angle * point) < 0;
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

    if (WindowManager::buttons['p'])
    {
        std::cout << pos_x << " " << pos_y << " "<< angle << "\n";
    }

    //if new pos is walkable update the position
    if((*map)((int)new_pos_x,(int)new_pos_y)->isWalkable()) 
    {
        pos_x = new_pos_x;
        pos_y = new_pos_y;
    }

    view_l = {sin(angle - field_of_view/2),cos(angle - field_of_view/2),0};
    view_r = {sin(angle + field_of_view/2),cos(angle + field_of_view/2),0};
}

Player::Player(){}