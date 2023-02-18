#include "obj/obj.hpp"

#include <vector>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

OBJ::OBJ::OBJ(std::string path)
{
    std::ifstream obj_file(path);
    if(!obj_file.is_open()) return;
    std::string line;

    while (std::getline(obj_file, line))
    {
        if(line.size() == 0 || line[0] == '#') continue; //ignore comments

        switch (line[0]*256+line[1])
        {
        case ('v'*256+ ' '):
            vertexes.push_back(Vertex(line));
            break;
        case ('v'*256+ 'n'):
            vertex_normals.push_back(VertexNormal(line));
            break;
        case ('v'*256+ 't'):
            texture_vertices.push_back(TextureVertex(line));
            break;
        case ('f'*256+ ' '):
            faces.push_back(Face(line));
            break;
        default:
            break;
        }
    }
}