#pragma once
#include <string>
#include <ostream>
namespace OBJ
{
    class VertexNormal
    {
        public:
        VertexNormal(std::string data);
        double x,y,z;
    };

}

std::ostream &operator<<(std::ostream &os, const OBJ::VertexNormal &v);