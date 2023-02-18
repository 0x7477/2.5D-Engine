#include "uv_point.hpp"

UVPoint::UVPoint() {}

UVPoint::UVPoint(OBJ::TextureVertex uv)
:u{uv.u},v{uv.v}{}

std::ostream &operator<<(std::ostream &os, const UVPoint &p)
{
    return os << "(" << p.u << "," << p.v << ")";
}
