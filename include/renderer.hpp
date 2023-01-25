#pragma once
#include "point.hpp"
class Game;

class Renderer
{
public:
    Renderer(Game* game);
    void render();

    static int getFloorScreenYPos(int screen_height, double distance);
    static int getCeilScreenYPos(int screen_height, double distance);
    static int getCeilScreenXPos(int screen_height, double distance);


    static double map(double x, double in_min, double in_max, double out_min, double out_max);

    double getRayAngle(int x);
    double getTextureSampleX(double ray_x, double ray_y);

    void renderObjects();
    void renderWalls();

    Game* game;
};