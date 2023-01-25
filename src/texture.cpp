#include "texture.hpp"
#include "colors.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>

Texture::Texture(std::string path)
{
    std::ifstream file(path, std::ifstream::in);
    if(!file.is_open())
    {
        checkboard(Color::black, Color::pink);
        return;
    }
    std::string data(std::istreambuf_iterator<char>{file}, {});
    memcpy(&pixel,data.substr(0x46).c_str(), 64*64*4);

    for(int x = 0; x < 64; x++)
        for(int y = 0; y < 64; y++)
        {
            unsigned char temp = pixel[x][y].r;
            pixel[x][y].a = pixel[x][y].a;
            pixel[x][y].g = pixel[x][y].g;
            pixel[x][y].r = pixel[x][y].b;
            pixel[x][y].b = temp;
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
    return pixel[y][x];
}