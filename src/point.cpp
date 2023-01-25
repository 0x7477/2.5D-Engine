#include "point.hpp"
#include "renderer.hpp"
#include "game.hpp"

WorldPoint::WorldPoint(double x, double y, double z)
: x{x}, y{y}, z{z} {}

WorldPoint::WorldPoint() {}


ScreenPoint::ScreenPoint(){}
ScreenPoint::ScreenPoint(Game* game, WorldPoint point)
{
    double dist_x = point.x - game->player.pos_x;
    double dist_y = point.y - game->player.pos_y;
    z = sqrt(dist_x * dist_x + dist_y * dist_y);

    double object_angle = atan2(cos(game->player.angle), sin(game->player.angle)) - atan2(dist_y, dist_x);

    if (object_angle < -M_PI)
        object_angle += 2 * M_PI;
    if (object_angle > M_PI)
        object_angle -= 2 * M_PI;

    // bool visible = (fabs(object_angle) < game->player.field_of_view / 2;
    x = (int)Renderer::map(object_angle, -game->player.field_of_view / 2, game->player.field_of_view / 2, 0, game->window_manager.screen->width);

    int floor = Renderer::getFloorScreenYPos(game->window_manager.screen->height, z);
    int ceil = Renderer::getCeilScreenYPos(game->window_manager.screen->height, z);

    y = floor + (int)((ceil - floor) * point.z);
}
ScreenPoint::ScreenPoint(int x, int y, float z)
: x{x}, y{y}, z{z} {}
