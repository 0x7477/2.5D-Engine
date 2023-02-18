#include "obj/texture_vertex.hpp"

OBJ::TextureVertex::TextureVertex(std::string data)
{
    std::sscanf(data.c_str(), "vt %lf %lf", &u, &v);
}

std::ostream& operator<<(std::ostream &os, const OBJ::TextureVertex &v)
{
    return os << "(" << v.u << "," << v.v << ")";
}