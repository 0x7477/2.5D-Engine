#pragma once
#include <string>
#include <ostream>
namespace OBJ
{
    class Vertex
    {
        public:
        Vertex(std::string data)
        {
            std::sscanf(data.c_str(), "v %lf %lf %lf %lf", &x, &y, &z, &w);
        }
        double x,y,z,w = 1;
    };

    std::ostream &operator<<(std::ostream &os, const OBJ::Vertex &v)
    {
        return os << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
}
