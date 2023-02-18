#pragma once
#include <string>
#include <ostream>
namespace OBJ
{
    class TextureVertex
    {
        public:
        TextureVertex(std::string data)
        {
            std::sscanf(data.c_str(), "vt %lf %lf", &u, &v);
        }
        double u,v;
    };

    std::ostream &operator<<(std::ostream &os, const OBJ::TextureVertex &v)
    {
        return os << "(" << v.u << "," << v.v << ")";
    }
}
