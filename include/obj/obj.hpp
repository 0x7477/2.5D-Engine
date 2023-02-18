#include "face.hpp"
#include "vertex_normal.hpp"
#include "vertex.hpp"
#include "worldpoint.hpp"
#include <vector>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

namespace OBJ
{
    std::vector<WorldPoint> loadOBJ(std::string path)
    {
        std::vector<WorldPoint> points{};
        std::ifstream obj_file(path);

        if(!obj_file.is_open()) return points;

        std::string line;

        std::vector<OBJ::Vertex> vertexes{};
        std::vector<OBJ::VertexNormal> vertex_normals{};
        std::vector<OBJ::Face> faces{};

        while (std::getline(obj_file, line))
        {
            if(line.size() == 0 || line[0] == '#') continue; //ignore comments

            switch (line[0]*256+line[1])
            {
            case ('v'*256+ ' '):
                vertexes.push_back(OBJ::Vertex(line));
                break;
            case ('v'*256+ 'n'):
                vertex_normals.push_back(OBJ::VertexNormal(line));
                break;
            case ('f'*256+ ' '):
                faces.push_back(OBJ::Face(line));
                break;
            default:
                break;
            }
        }

        for(const auto& face : faces)
        {
            auto p1 = vertexes[face.indices[0].vertex-1];
            auto p2 = vertexes[face.indices[1].vertex-1];
            auto p3 = vertexes[face.indices[2].vertex-1];

            points.push_back({p1.x,p1.y,p1.z});
            points.push_back({p2.x,p2.y,p2.z});
            points.push_back({p3.x,p3.y,p3.z});
        }

        return points;
    }


}