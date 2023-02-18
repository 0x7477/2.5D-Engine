#pragma once
#include "pixel.hpp"
#include <filesystem>

/// @brief A texture for objects and walls
class Texture
{
    private:
    void initMemory();
    public:
    Texture(unsigned int width = 64,unsigned int height = 64);
    /// @brief loads a texture
    /// @param path the path of the texture
    Texture(std::string path);
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
    : width{other.width}, height{other.height}, pixel{other.pixel} {}
 
    Texture(Texture&& other) noexcept // move constructor
    : width{other.width}, height{other.height},pixel(std::exchange(other.pixel, nullptr)) {    }

 
    Texture& operator=(const Texture& other) // copy assignment
    {
        return *this = Texture(other);
    }
 
    Texture& operator=(Texture&& other) noexcept // move assignment
    {
        std::swap(height, other.height);
        std::swap(width, other.width);
        std::swap(pixel, other.pixel);

        return *this;
    }

    unsigned int width, height;
    /// @brief The Buffer is set to constant 64x64 Pixel
    Pixel** pixel;
};