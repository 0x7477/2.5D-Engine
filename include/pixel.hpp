#pragma once 
typedef struct Pixel
{    
    /// @brief default constor
    Pixel();
    /// @brief create a color from integer with alpha 255
    /// @param rgba first byte is red, second byte is green, third byte is blue, alpha is 255  
    Pixel(int rgba);

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;
} Pixel;

