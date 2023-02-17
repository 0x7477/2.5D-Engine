#include "quaternion.hpp"
#include "worldpoint.hpp"
#include <cmath>

std::ostream &operator<<(std::ostream &os, const Quaternion &p)
{
    return os << "(" << p.w << "," << p.x << "," << p.y << "," << p.z << ")";
}

Quaternion Quaternion::identity{1, 0, 0, 0};

Quaternion::Quaternion(double w, double x, double y, double z)
    : w{w}, x{x}, y{y}, z{z} {}

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

WorldPoint Quaternion::operator*(const WorldPoint &p) const
{
    WorldPoint f1 = p * (w * w - (x * x + y * y + z * z));

    double scalar = p.x * x + p.y * y + p.z * z;
    WorldPoint f2 = WorldPoint{x, y, z} * 2 * scalar;
    WorldPoint f3 = WorldPoint::crossProduct({x,y,z}, p) * 2 * w;

    WorldPoint res = f1 + f2 + f3;
    return res;
}