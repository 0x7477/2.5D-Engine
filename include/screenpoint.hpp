#pragma once
#include <iostream>
class Game;
class Screen;
class Quaternion;

class WorldPoint;

/// @brief A point in screenspace
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
