#pragma once
#include <iostream>
#include "obj/texture_vertex.hpp"


/// @brief A point in screenspace
class UVPoint
{

public:
    UVPoint();
    UVPoint(double u, double v);
    UVPoint(OBJ::TextureVertex uv);
    double u = 0, v = 0;
};

std::ostream &operator<<(std::ostream &os, const UVPoint &p);
