#include "obj/vertex_normal.hpp"

OBJ::VertexNormal::VertexNormal(std::string data)
{
    std::sscanf(data.c_str(), "vn %lf %lf %lf", &x, &y, &z);
}

std::ostream& operator<<(std::ostream &os, const OBJ::VertexNormal &v)
{
    return os << "(" << v.x << "," << v.y << "," << v.z << ")";
}