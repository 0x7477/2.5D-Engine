#pragma once

#include "world_point.hpp"
#include "quaternion.hpp"

class Transform
{
    public:
    Transform(const WorldPoint& pos, const Quaternion& rot, double scale);
    WorldPoint pos;
    Quaternion rot;
    double scale;
};
