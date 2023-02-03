#include "billboard.hpp"
#include "game.hpp"
#include "point.hpp"
#include <iostream>

Billboard::Billboard(WorldPoint pos, std::string texture, double width, double height)
:pos{pos}, width{width}, height{height}, texture{&(Game::textures[texture])}{}



bool Billboard::isVisible(Player* player) const
{
    double angle = pos.getAngle(player), distance = pos.getDistance(player);
    return (fabs(angle) - fabs(atan2(distance, width / 2))) < player->field_of_view / 2;
}
