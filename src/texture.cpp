#include "texture.hpp"
#include "colors.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>


Texture::~Texture()
{
    for(auto x = 0ul; x < width; x++)
        free(pixel[x]);
    free(pixel);
}

Texture::Texture(int width,int height)
:width{width},height{height}
{
    initMemory();
    checkboard(Color::black, Color::pink);
};

void Texture::initMemory()
{
    pixel = (Pixel **) malloc(sizeof(Pixel*) * width);
    for(auto x = 0ul; x < width; x++)
        pixel[x] = (Pixel *) malloc(sizeof(Pixel) * height);
}

Texture::Texture(std::string path, int width,int height)
:width{width},height{height}
{
    initMemory();
    std::ifstream file(path, std::ifstream::in);
    if(!file.is_open())
    {
        //replace texture with checkboard pattern
        checkboard(Color::black, Color::pink);
        return;
    }

    std::string data(std::istreambuf_iterator<char>{file}, {});

    //cut header
    data = data.substr(0x46);

    unsigned int index = 0;
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            pixel[y][x].a = data[index+3];
            pixel[y][x].r = data[index+2];
            pixel[y][x].g = data[index+1];
            pixel[y][x].b = data[index];
            index += 4;
        }
}

void Texture::checkboard(Pixel color1,Pixel color2)
{
    for(int x = 0; x < 64; x++)
        for(int y = 0; y < 64; y++)
            pixel[x][y] = (x+y)%2?color1:color2;
}

void Texture::fill(Pixel color)
{
    for(int x = 0; x < 64; x++)
        for(int y = 0; y < 64; y++)
            pixel[x][y] = color;
}

void drawPixel(int r, int g, int b)
{
    std::cout <<  std::string("\033[38;2;"+std::to_string(r) + ";"+std::to_string(g)+ ";"+std::to_string(b)+"m█");
}

void Texture::draw()
{
    for(int x = 0; x < 64; x++)
    {
        for(int y = 0; y < 64; y++)
            drawPixel(pixel[x][y].r,pixel[x][y].g,pixel[x][y].b);

        std::cout << "\033[0m\n";
    }
}

Pixel Texture::operator()(int x, int y)
{
    return pixel[x][y];
}