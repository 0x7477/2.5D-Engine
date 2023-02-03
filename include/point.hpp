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
    double getAngle(const Player* player) const;
    double getDistance(const Player* player) const;

    double x = 0, y = 0, z = 0;
};

class ScreenPoint
{

public:
    ScreenPoint();
    ScreenPoint(Game *game, WorldPoint point);
    ScreenPoint(int x, int y, float z);

    bool isOnScreen(Screen *screen);
    int x = 0, y = 0;
    float z = 0;
};

std::ostream &operator<<(std::ostream &os, const ScreenPoint &p);

std::ostream &operator<<(std::ostream &os, const WorldPoint &p);

std::ostream &operator<<(std::ostream &os,const Quaternion& p);