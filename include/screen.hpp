#pragma once

#include "pixel.hpp"

/// @brief The screen buffer
class Screen
{
    public: 

    /// @brief Initialize a screen buffer
    /// @param width the width in pixels
    /// @param height the height in pixels
    Screen(int width, int height);
    ~Screen();
    Screen(const Screen&) = delete;
    Screen(Screen&& other) = delete;
    Screen& operator=(const Screen&) = delete;
    Screen& operator=(Screen&& other) = delete;
    
    /// @brief set the pixels color
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @param color the color to be set
    void setColor(int x, int y, Pixel color);

    /// @brief gets the zBuffer at x,y
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @return the Depth at (x,y)
    float getDepth(int x, int y);

    /// @brief set the pixels depth
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @param depth the depth to be set
    void setDepth(int x, int y, float depth);

    /// @brief fills the screen with a color
    /// @param color the color o be filled
    void fill(Pixel color);

    /// @brief fills the zBuffer with a depth
    /// @param depth the depth to be filled
    void fillZBuffer(float depth = __FLT_MAX__);

    const int width; int height;
    Pixel* buffer;
    float* depthmap;


};