#include "obj/face.hpp"
#include <string>

OBJ::Face::Face(std::string data)
{
    std::sscanf(data.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &indices[0].vertex, &indices[0].vertexTexture, &indices[0].vertexNormal,
                &indices[1].vertex, &indices[1].vertexTexture, &indices[1].vertexNormal,
                &indices[2].vertex, &indices[2].vertexTexture, &indices[2].vertexNormal);

    indices[0].vertex--;
    indices[1].vertex--;
    indices[2].vertex--;

    indices[0].vertexTexture--;
    indices[1].vertexTexture--;
    indices[2].vertexTexture--;

    indices[0].vertexNormal--;
    indices[1].vertexNormal--;
    indices[2].vertexNormal--;
}


std::ostream& operator<<(std::ostream &os, const OBJ::Face &v)
{
    return os << "(" << v.indices[0].vertex << "," << v.indices[0].vertexTexture << "," << v.indices[0].vertexNormal << ")"
                << "(" << v.indices[1].vertex << "," << v.indices[1].vertexTexture << "," << v.indices[1].vertexNormal << ")"
                << "(" << v.indices[2].vertex << "," << v.indices[2].vertexTexture << "," << v.indices[2].vertexNormal << ")";
}
