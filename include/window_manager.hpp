#pragma once
#include "screen.hpp"

class Game;

class WindowManager
{
    public: 
    WindowManager(int argc, char ** argv, Game* game);

    static void reshape(int width, int height);

    static void start();
    static void update();
    void draw();

    static void pressKey(unsigned char key, int x, int y);
    static void releaseKey(unsigned char key, int x, int y);

    static int window_height, window_width;

    inline static Screen* screen;
    static Game* game;
    static inline bool buttons[256];


};