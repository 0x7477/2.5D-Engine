#pragma once

#include "pixel.hpp"

class Screen
{
    public: 

    Screen(int width, int height);
    ~Screen();
    Screen(const Screen&) = delete;
    Screen(Screen&& other) = delete;
    Screen& operator=(const Screen&) = delete;
    Screen& operator=(Screen&& other) = delete;
    

    const int width; int height;
    

    Pixel* buffer;
    float* depthmap;
    void setColor(int x, int y, Pixel color);

    float getDepth(int x, int y);
    void setDepth(int x, int y, float depth);

    void fill(Pixel color);
    void fillZBuffer(float depth = 0);


};