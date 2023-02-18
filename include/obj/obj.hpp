#pragma once
#include "face.hpp"
#include "vertex_normal.hpp"
#include "vertex.hpp"
#include "texture_vertex.hpp"
#include "world_point.hpp"

#include <vector>
#include <string>
namespace OBJ
{

    class OBJ
    {
        public:
        OBJ(std::string path);

        std::vector<Vertex> vertexes{};
        std::vector<VertexNormal> vertex_normals{};
        std::vector<TextureVertex> texture_vertices{};
        std::vector<Face> faces{};
    };
}