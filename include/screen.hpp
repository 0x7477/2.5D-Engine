#pragma once

#include "pixel.hpp"

/// @brief The screen buffer
class Screen
{
    public: 

    /// @brief Initialize a screen buffer
    /// @param width the width in pixels
    /// @param height the height in pixels
    Screen(std::size_t width, std::size_t height);
    ~Screen();
    Screen(const Screen&) = delete;
    Screen(Screen&& other) = delete;
    Screen& operator=(const Screen&) = delete;
    Screen& operator=(Screen&& other) = delete;
    
    /// @brief set the pixels color
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @param color the color to be set
    void setColor(std::size_t x, std::size_t y, Pixel color);

    /// @brief gets the zBuffer at x,y
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @return the Depth at (x,y)
    float getDepth(std::size_t x, std::size_t y);

    /// @brief set the pixels depth
    /// @param x the x pixel chord
    /// @param y the y pixel chord
    /// @param depth the depth to be set
    void setDepth(std::size_t x, std::size_t y, float depth);

    /// @brief fills the screen with a color
    /// @param color the color o be filled
    void fill(Pixel color);

    /// @brief fills the zBuffer with a depth
    /// @param depth the depth to be filled
    void fillZBuffer(float depth = __FLT_MAX__);

    const std::size_t width; std::size_t height;
    Pixel* buffer;
    float* depthmap;


};