#pragma once
#include "pixel.hpp"
#include <filesystem>

/// @brief A texture for objects and walls
class Texture
{
    public:
    Texture();
    /// @brief loads a texture
    /// @param path the path of the texture
    Texture(std::string path);

    /// @brief get color at x and y position
    /// @param x the x chord
    /// @param y the y chord
    /// @return the color at given location
    Pixel operator()(int x, int y);
    /// @brief draws the texture in the terminal
    void draw();
    /// @brief fills the Texture with a solid color
    /// @param color the color to be filled
    void fill(Pixel color);
    
    /// @brief fills the Texture in a checkboard pattern
    /// @param color1 the first color in the pattern
    /// @param color2 the second color in the pattern
    void checkboard(Pixel color1,Pixel color2);

    
    /// @brief The Buffer is set to constant 64x64 Pixel
    Pixel pixel[64][64] = {};    
};