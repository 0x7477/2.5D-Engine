#include "mesh.hpp"
#include <iostream>


Mesh::Mesh(Game* game, std::vector<Pixel> colors, const WorldPoint& pos,Quaternion rot,  double scale , std::vector<WorldPoint> vertices)
:game{game},pos{pos},rot{rot},scale{scale}, colors{colors},vertices{vertices}{};


void Mesh::draw()
{
    for(std::size_t i = 0; 3*i < vertices.size(); i ++)
    {
        ScreenPoint p1 = {game, (rot * vertices[3*i]  )*scale + pos};
        ScreenPoint p2 = {game, (rot * vertices[3*i+1])*scale + pos};
        ScreenPoint p3 = {game, (rot * vertices[3*i+2])*scale + pos};
        Triangle t{game->window_manager.screen, colors[i],p1,p2,p3};
        t.draw();
    }
}