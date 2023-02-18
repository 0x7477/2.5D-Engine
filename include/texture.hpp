#pragma once
#include "pixel.hpp"
#include <filesystem>

/// @brief A texture for objects and walls
class Texture
{
    private:
    void initMemory();
    public:
    Texture(int width = 64,int height = 64);
    /// @brief loads a texture
    /// @param path the path of the texture
    Texture(std::string path,int width = 64, int height = 64);
    ~Texture();
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

    
    Texture(const Texture& other) // copy constructor
    : pixel{other.pixel}, width{other.width}, height{other.height} {}
 
 
    Texture(Texture&& other) noexcept // move constructor
    : pixel(std::exchange(other.pixel, nullptr)),width{other.width}, height{other.height} {}
 
    Texture& operator=(const Texture& other) // copy assignment
    {
        return *this = Texture(other);
    }
 
    Texture& operator=(Texture&& other) noexcept // move assignment
    {
        std::swap(pixel, other.pixel);
        width = other.width;
        height = other.height;
        return *this;
    }
    /// @brief The Buffer is set to constant 64x64 Pixel
    Pixel** pixel;

    int width, height;
};