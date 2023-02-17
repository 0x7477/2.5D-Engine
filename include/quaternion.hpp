#pragma once
#include <iostream>

class WorldPoint;

/// @brief A Quaternion class
class Quaternion
{
public:
    Quaternion(double x, double y, double z);
    Quaternion(double w, double x, double y, double z);

    WorldPoint operator*(const WorldPoint& p) const;

    double w = 0, x = 0, y = 0, z = 0;

    static Quaternion identity;
};

std::ostream &operator<<(std::ostream &os,const Quaternion& p);