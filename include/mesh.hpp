#include <vector>
#include "triangle.hpp"
#include "screen.hpp"
class Mesh
{
    Mesh(Screen* screen, double x, double y, double z);
    double x,y,z;

    void draw();
    std::vector<Triangle> triangles;
};