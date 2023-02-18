#pragma once
#include "worldpoint.hpp"

class DirectionalLight
{
    public:
    DirectionalLight(WorldPoint direction, float intensity);

    WorldPoint getDirection() const;

    private:
    WorldPoint direction;
    float intensity;
};