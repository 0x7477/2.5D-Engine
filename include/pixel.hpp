#pragma once 
typedef struct Pixel
{    
    Pixel(){
        a = 255;
    };


    Pixel(int rgba)
    {
        r = (rgba & 0xFF0000) >>16;
        g = (rgba & 0xFF00) >> 8;
        b = (rgba & 0xFF);
        a = 255;
    };

    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;
} Pixel;

