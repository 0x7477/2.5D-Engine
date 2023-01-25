#pragma once
#include "pixel.hpp"
#include <filesystem>
class Texture
{
    public:
    Texture(){};
    Texture(std::string path);

    Pixel operator()(int x, int y);
    void draw();
    void fill(Pixel color);
    void checkboard(Pixel color1,Pixel color2);
    Pixel pixel[64][64] = {};    
};