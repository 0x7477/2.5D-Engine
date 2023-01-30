#include <vector>
#include "triangle.hpp"
#include "game.hpp"
#include "point.hpp"
class Mesh
{

public:
    Mesh(Game* game, std::vector<Pixel> colors, const WorldPoint& pos,Quaternion rot,  double scale, std::vector<WorldPoint> vertices);
    Game* game;
    WorldPoint pos;
    Quaternion rot;
    double scale;
    std::vector<Pixel> colors;

    void draw();
    std::vector<WorldPoint> vertices;
};