#include "texture.hpp"
#include "colors.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>


Texture::~Texture()
{
    for(std::size_t x = 0; x < width; x++)
    {
        free(pixel[x]);
    }
    free(pixel);
}

Texture::Texture(unsigned int width,unsigned int height)
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

Texture::Texture(std::string path)
{
    std::ifstream file(path, std::ifstream::in);
    if(!file.is_open())
    {
        width = 64;
        height = 64;

        initMemory();

        //fill texture with checkboard pattern
        checkboard(Color::black, Color::pink);
        return;
    }

    std::string data(std::istreambuf_iterator<char>{file}, {});

    width = *((int*)&data[0x12]);
    height = *((int*)&data[0x16]); //only works for little endian systems 
    
    //cut header (at 0xA is the length of header defined)
    data = data.substr((unsigned char)data[0xA]);

    initMemory();

    int index = 0;
    for(std::size_t y = 0; y < height; y++)
    {
    for(std::size_t x = 0; x < width; x++)
        {
            pixel[x][y].a = data[index+3];
            pixel[x][y].r = data[index+2];
            pixel[x][y].g = data[index+1];
            pixel[x][y].b = data[index];
            index += 4;
        }
    }
}

void Texture::checkboard(Pixel color1,Pixel color2)
{
    for(std::size_t x = 0; x < width; x++)
        for(std::size_t y = 0; y < height; y++)
            pixel[x][y] = (x+y)%2?color1:color2;
}

void Texture::fill(Pixel color)
{
    for(std::size_t x = 0; x < width; x++)
        for(std::size_t y = 0; y < height; y++)
            pixel[x][y] = color;
}

void drawPixel(int r, int g, int b)
{
    std::cout <<  std::string("\033[38;2;"+std::to_string(r) + ";"+std::to_string(g)+ ";"+std::to_string(b)+"m█");
}

void Texture::draw()
{
    for(std::size_t y = height; y --> 0 ;)
    {
        for(std::size_t x = 0; x < width; x++)
        {
            auto p = pixel[x][y];
            if(p.a == 0)
            {
                std::cout << " ";
                continue;
            }
            drawPixel(p.r,p.g,p.b);

        }
            std::cout << y;
            std::cout << "\033[0m\n";    
            

    }
}

Pixel Texture::operator()(const int& x, const int& y) const
{
    return pixel[x][y];
}


Pixel Texture::operator()(const float& x, const float& y) const
{
    return pixel[(int)(x*(width))][(int)(y*(height))];
}

Pixel Texture::operator()(const double& x, const double& y) const
{
    return pixel[(int)(x*(width))][(int)(y*(height))];
}