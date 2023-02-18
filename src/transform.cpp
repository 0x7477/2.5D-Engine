#include "transform.hpp"

Transform::Transform(const WorldPoint& pos, const Quaternion& rot, double scale)
:pos{pos},rot{rot},scale{scale} {}
