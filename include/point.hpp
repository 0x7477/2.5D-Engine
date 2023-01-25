#pragma once
class Game;

class ScreenPoint;

class WorldPoint
{

public:
    WorldPoint();
    WorldPoint(double x, double y, double z);

    double x, y, z;
};


class ScreenPoint
{

public:
    ScreenPoint();
    ScreenPoint(Game* game, WorldPoint point);
    ScreenPoint(int x, int y, float z);

    int x, y;
    float z;
};