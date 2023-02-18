#include "obj/vertex.hpp"

OBJ::Vertex::Vertex(std::string data)
{
    std::sscanf(data.c_str(), "v %lf %lf %lf", &p.x, &p.y, &p.z);
}

std::ostream& operator<<(std::ostream &os, const OBJ::Vertex &v)
{
    return os << "(" << v.p.x << "," << v.p.y << "," << v.p.z << ")";
}
