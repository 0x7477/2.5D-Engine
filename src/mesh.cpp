#include "mesh.hpp"
#include <iostream>


Mesh::Mesh(Game* game, std::vector<Pixel> colors, const WorldPoint& pos,Quaternion rot,  double scale , std::vector<WorldPoint> vertices)
:game{game},pos{pos},rot{rot},scale{scale}, colors{colors},vertices{vertices}{};


void Mesh::draw() const
{
    for(std::size_t i = 0; 3*i < vertices.size(); i ++)
    {
        //apply transformations
        WorldPoint w1{rot * vertices[3*i]   * scale + pos};
        WorldPoint w2{rot * vertices[3*i+1] * scale + pos};
        WorldPoint w3{rot * vertices[3*i+2] * scale + pos};

        //check visibility
        if(!game->player.isVisible(w1) && !game->player.isVisible(w2) && !game->player.isVisible(w3)) continue;

        //convert two screen pos
        ScreenPoint p1{game, w1};
        ScreenPoint p2{game, w2};
        ScreenPoint p3{game, w3};

        //draw triangle
        Triangle{game->window_manager.screen, colors[i],p1,p2,p3}.draw();
    }
}