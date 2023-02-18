#pragma once
#include <string>
#include <ostream>
#include "world_point.hpp"
namespace OBJ
{
    class Vertex
    {
        public:
        Vertex(std::string data);
        WorldPoint p;
    };

}

std::ostream &operator<<(std::ostream &os, const OBJ::Vertex &v);