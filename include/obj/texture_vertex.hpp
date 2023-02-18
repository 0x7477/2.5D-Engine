#pragma once
#include <string>
#include <ostream>
namespace OBJ
{
    class TextureVertex
    {
        public:
        TextureVertex(std::string data);
        double u,v;
    };

}

std::ostream &operator<<(std::ostream &os, const OBJ::TextureVertex &v);