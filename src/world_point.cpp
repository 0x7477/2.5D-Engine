#include "world_point.hpp"
#include "player.hpp"
#include <iostream>

WorldPoint::WorldPoint(double x, double y, double z)
    : x{x}, y{y}, z{z} {}

WorldPoint::WorldPoint() {}

WorldPoint WorldPoint::operator+(const WorldPoint &p2) const
{
    return {x + p2.x, y + p2.y, z + p2.z};
}

WorldPoint WorldPoint::operator-(const WorldPoint &p2) const
{
    return {x - p2.x, y - p2.y, z - p2.z};
}

WorldPoint WorldPoint::crossProduct(const WorldPoint &p1, const WorldPoint &p2)
{
    return {p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x};
}

WorldPoint WorldPoint::getNormalizedNormalVector(WorldPoint p1, WorldPoint p2) const
{
    WorldPoint vec1 = p1 - *this;
    WorldPoint vec2 = p2 - *this;

    WorldPoint normal = crossProduct(vec1, vec2);
    normal.normalize();

    return normal;
}
float WorldPoint::getLength() const
{
    return (float)(x * x + y * y + z * z);
}

float inverseSquareRoot(const float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;           // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y)); // 1st iteration
                                         //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

void WorldPoint::normalize()
{
    float length = getLength();

    float normalization_length = inverseSquareRoot(length);

    x *= normalization_length;
    y *= normalization_length;
    z *= normalization_length;
}
double WorldPoint::operator*(const WorldPoint &p2) const
{
    return x * p2.x + y * p2.y + z * p2.z;
}

WorldPoint WorldPoint::operator*(double scale) const
{
    return {x * scale, y * scale, z * scale};
}

double WorldPoint::getAngle(const Player *player) const
{
    double dist_x = x - player->pos_x;
    double dist_y = y - player->pos_y;

    double object_angle = atan2(cos(player->angle), sin(player->angle)) - atan2(dist_y, dist_x);

    // normalize
    if (object_angle < -M_PI)
        object_angle += 2 * M_PI;
    else if (object_angle > M_PI)
        object_angle -= 2 * M_PI;

    return object_angle;
}

double WorldPoint::getDistance(const Player *player) const
{
    double dist_x = x - player->pos_x;
    double dist_y = y - player->pos_y;

    return sqrt(dist_x * dist_x + dist_y * dist_y);
}

std::ostream &operator<<(std::ostream &os, const WorldPoint &p)
{
    return os << "(" << p.x << "," << p.y << "," << p.z << ")";
}