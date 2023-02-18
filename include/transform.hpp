#pragma once

#include "worldpoint.hpp"
#include "quaternion.hpp"

class Transform
{
    public:
    Transform(const WorldPoint& pos, const Quaternion& rot, double scale);
    WorldPoint pos;
    Quaternion rot;
    double scale;
};
