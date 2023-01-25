#pragma once
#include "texture.hpp"
#include <string>

class Billboard
{
public:
    Billboard(double x, double y, std::string texture, double width =1, double height = 1);
    double x,y;
    double width,height;
    Texture* texture;
};