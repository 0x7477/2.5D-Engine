#pragma once
#include <ostream>
namespace OBJ
{
    typedef struct FaceVertexIndices
    {
        int vertex;
        int vertexTexture;
        int vertexNormal;

    } FaceVertexIndices;

    class Face
    {
    public:
        Face(std::string data);
        FaceVertexIndices indices[3];
    };

}

std::ostream &operator<<(std::ostream &os, const OBJ::Face &v);