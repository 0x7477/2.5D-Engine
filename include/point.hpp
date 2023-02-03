#pragma once
#include <iostream>
#include <cmath>
class Game;
class Screen;
class Player;

class ScreenPoint;
class WorldPoint;

class Quaternion
{
public:
    Quaternion(double x, double y, double z);
    Quaternion(double w, double x, double y, double z);

    WorldPoint operator*(const WorldPoint& p) const;

    double w = 0, x = 0, y = 0, z = 0;

    static Quaternion identity;
};

class WorldPoint
{

public:
    WorldPoint();
    WorldPoint(double x, double y, double z);
    WorldPoint operator+(const WorldPoint &p2) const;
    WorldPoint operator*(double scale) const;
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

class ScreenPoint
{

public:
    ScreenPoint();
    /// @brief convert a Worldpoint to a screenpoint 
    ScreenPoint(Game *game, WorldPoint point);
    ScreenPoint(int x, int y, float z);

    /// @brief checks if a screenpoint is inside screens bounds
    /// @param screen the screen to be checked
    /// @return returns if the screenpoint is inside screens bounds

    bool isOnScreen(Screen *screen);
    int x = 0, y = 0;
    float z = 0;
};

std::ostream &operator<<(std::ostream &os, const ScreenPoint &p);

std::ostream &operator<<(std::ostream &os, const WorldPoint &p);

std::ostream &operator<<(std::ostream &os,const Quaternion& p);