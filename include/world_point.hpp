#pragma once

#include <iostream>

class Player;
/// @brief A point in worldspace
class WorldPoint
{

public:
    WorldPoint();
    WorldPoint(double x, double y, double z);
    WorldPoint operator+(const WorldPoint &p2) const;
    WorldPoint operator-(const WorldPoint &p2) const;
    WorldPoint operator*(double scale) const;
    double operator*(const WorldPoint &p2) const;

    static WorldPoint crossProduct(const WorldPoint &p1,const WorldPoint &p2);

    float getLength() const;
    void normalize();
    WorldPoint getNormalizedNormalVector(WorldPoint p1, WorldPoint p2) const;
    /// @brief get the angle relative to the player
    /// @param player the player
    /// @return returns the angle relative to the player
    double getAngle(const Player* player) const;

    /// @brief get the distance relative to the players position
    /// @param player the player
    /// @return returns the distance relative to the players position
    double getDistance(const Player* player) const;

    double x = 0, y = 0, z = 0;
};

std::ostream &operator<<(std::ostream &os, const WorldPoint &p);
