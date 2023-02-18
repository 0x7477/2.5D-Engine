#include "directional_light.hpp"


DirectionalLight::DirectionalLight(WorldPoint direction, float intensity)
:direction{direction}, intensity{intensity}
{

}

WorldPoint DirectionalLight::getDirection() const
{
    return direction;
}