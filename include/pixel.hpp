#pragma once 
#include <iostream>
/// @brief A Pixel in the screen buffer
typedef struct Pixel
{    
    /// @brief default constor
    Pixel();
    /// @brief create a color from integer with alpha 255
    /// @param rgba first byte is red, second byte is green, third byte is blue, alpha is 255  
    Pixel(int rgba);


    void setBrightness(float brightness);

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;
} Pixel;



std::ostream &operator<<(std::ostream &os, const Pixel &p);
