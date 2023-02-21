#include "screen_point.hpp"
#include "renderer.hpp"
#include "game.hpp"
#include "world_point.hpp"


ScreenPoint::ScreenPoint() {}

ScreenPoint::ScreenPoint(Game *game, WorldPoint point)
{
    const auto object_angle = point.getAngle(&game->player);
    z = (float)point.getDistance(&game->player);

    // map the angle to screenspace
    x = (int)Renderer::map(object_angle, -game->player.field_of_view / 2, game->player.field_of_view / 2, 0, game->window_manager.screen->width);

    int floor = Renderer::getFloorScreenYPos(game->window_manager.screen->height,z);
    int ceil = Renderer::getCeilScreenYPos(game->window_manager.screen->height,z);

    // interpolate z from floor to ceil
    y = (int)Renderer::map(point.z, 0, 1, floor, ceil);
}

ScreenPoint::ScreenPoint(int x, int y, float z)
    : x{x}, y{y}, z{z} {}

bool ScreenPoint::isOnScreen(Screen *screen)
{
    return x >= 0 && x < (int)screen->width && y >= 0 && y < (int)screen->height;
}

std::ostream &operator<<(std::ostream &os, const ScreenPoint &p)
{
    return os << "(" << p.x << "," << p.y << "," << p.z << ")";
}