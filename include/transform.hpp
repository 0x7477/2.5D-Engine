#pragma once

#include "worldpoint.hpp"
#include "quaternion.hpp"

class Transform
{
    Transform(const WorldPoint& pos, const Quaternion& rot, double scale);
    WorldPoint pos;
    Quaternion rot;
    double scale;
};
