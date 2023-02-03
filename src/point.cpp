#include "point.hpp"
#include "renderer.hpp"
#include "game.hpp"



WorldPoint::WorldPoint(double x, double y, double z)
: x{x}, y{y}, z{z} {}

WorldPoint::WorldPoint() {}

WorldPoint WorldPoint::operator+(const WorldPoint& p2) const
{
    return {x + p2.x, y + p2.y, z + p2.z};   
}

WorldPoint WorldPoint::operator*(double scale) const
{
    return {x *scale, y *scale, z *scale};   
}

double WorldPoint::getAngle(const Player* player) const
{
    double dist_x = x - player->pos_x;
    double dist_y = y - player->pos_y;

    double object_angle = atan2(cos(player->angle), sin(player->angle)) - atan2(dist_y, dist_x);

    if (object_angle < -M_PI)
        object_angle += 2 * M_PI;
    else if (object_angle > M_PI)
        object_angle -= 2 * M_PI;

    return object_angle;
}

double WorldPoint::getDistance(const Player* player) const
{
    double dist_x = x - player->pos_x;
    double dist_y = y - player->pos_y;

    return sqrt(dist_x * dist_x + dist_y * dist_y);
}

ScreenPoint::ScreenPoint(){}

ScreenPoint::ScreenPoint(Game* game, WorldPoint point)
{
    double dist_x = point.x - game->player.pos_x;
    double dist_y = point.y - game->player.pos_y;
    z = (float)sqrt(dist_x * dist_x + dist_y * dist_y);

    double object_angle = atan2(cos(game->player.angle), sin(game->player.angle)) - atan2(dist_y, dist_x);

    if (object_angle < -M_PI)
        object_angle += 2 * M_PI;
    else if (object_angle > M_PI)
        object_angle -= 2 * M_PI;

    // bool visible = (fabs(object_angle) < game->player.field_of_view / 2;
    x = (int)Renderer::map(object_angle, -game->player.field_of_view / 2, game->player.field_of_view / 2, 0, game->window_manager.screen->width);

    int floor = Renderer::getFloorScreenYPos(game->window_manager.screen->height, z);
    int ceil = Renderer::getCeilScreenYPos(game->window_manager.screen->height, z);

    y = floor + (int)((ceil - floor) * point.z);
}

ScreenPoint::ScreenPoint(int x, int y, float z)
: x{x}, y{y}, z{z} {}


bool ScreenPoint::isOnScreen(Screen* screen)
{
    return x >= 0 && x < screen->width && y >= 0 && y < screen->height;
}


 std::ostream &operator<<(std::ostream &os, const ScreenPoint& p) { 
    return os << "("<< p.x << "," << p.y << "," << p.z << ")";
}

    std::ostream &operator<<(std::ostream &os,const WorldPoint& p) { 
    return os << "("<< p.x << "," << p.y << "," << p.z << ")";
}

    std::ostream &operator<<(std::ostream &os,const Quaternion& p) { 
    return os << "("<< p.w << "," << p.x << "," << p.y<<"," << p.z << ")";
}
Quaternion Quaternion::identity{1,0,0,0};

Quaternion::Quaternion(double w, double x, double y, double z)
: w{w}, x{x}, y{y}, z{z}{}

Quaternion::Quaternion(double x_, double y_, double z_)
    {
        double cr = cos(x_ * 0.5);
        double sr = sin(x_ * 0.5);
        double cp = cos(y_ * 0.5);
        double sp = sin(y_ * 0.5);
        double cy = cos(z_ * 0.5);
        double sy = sin(z_ * 0.5);

        w = cr * cp * cy + sr * sp * sy;
        x = sr * cp * cy - cr * sp * sy;
        y = cr * sp * cy + sr * cp * sy;
        z = cr * cp * sy - sr * sp * cy;
    }

    WorldPoint Quaternion::operator*(const WorldPoint& p) const
    {
        WorldPoint f1 = p * (w*w - (x*x + y*y + z*z));

        double scalar = p.x * x + p.y * y + p.z * z;
        WorldPoint f2 = WorldPoint{x,y,z} * 2 * scalar;
        WorldPoint f3 = WorldPoint{y*p.z - z * p.y,z*p.x - x * p.z,x*p.y - y * p.x} * 2 * w;

        // std::cout << "\n=========" << "\n";

        // std::cout << f1 << "\n";
        // std::cout << f2<< "\n";
        // std::cout << f3 << "\n";

        //         std::cout << "=========" << "\n";

        WorldPoint res = f1 + f2 + f3;
        return res;
    }