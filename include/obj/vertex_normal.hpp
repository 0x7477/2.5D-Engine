#pragma once
#include <string>
#include <ostream>
namespace OBJ
{
    class VertexNormal
    {
        public:
        VertexNormal(std::string data)
        {
            std::sscanf(data.c_str(), "vn %lf %lf %lf", &x, &y, &z);
        }
        double x,y,z;
    };

    std::ostream &operator<<(std::ostream &os, const OBJ::VertexNormal &v)
    {
        return os << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
}
