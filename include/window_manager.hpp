#pragma once
#include "screen.hpp"

class Game;

/// @brief A window management utility for the game
class WindowManager
{
    public: 
    /// @brief Opens a Window
    /// @param argc the argument count
    /// @param argv the argument vector
    /// @param game the game
    WindowManager(int argc, char ** argv, Game* game);

    /// @brief window reshape callback
    /// @param width the new screen width
    /// @param height the new screen height
    static void reshape(int width, int height);


    /// @brief the start callback
    static void start();

    /// @brief the update callback
    static void update();
    /// @brief draws the screen buffer to the window
    void draw();

    /// @brief the callback when a key is pressed
    /// @param key the key pressed
    /// @param x the mouse x pos
    /// @param y the mouse y pos
    static void pressKey(unsigned char key, int x, int y);

    /// @brief the callback when a key is lifted
    /// @param key the key lifted
    /// @param x the mouse x pos
    /// @param y the mouse y pos
    static void releaseKey(unsigned char key, int x, int y);

    static int window_height, window_width;

    inline static Screen* screen;
    static Game* game;
    static inline bool buttons[256];


};