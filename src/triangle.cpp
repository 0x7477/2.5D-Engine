#include "triangle.hpp"
#include "game.hpp"
#include <iostream>


Triangle::Triangle(Game* game,Pixel color, const WorldPoint& w1, const WorldPoint& w2, const WorldPoint& w3)
:screen{game->window_manager.screen}, color{color}
{
    ScreenPoint p1{game,w1}, p2{game,w2}, p3{game,w3};

    edges[0] = Edge(this, p1, p2);
    edges[1] = Edge(this, p2, p3);
    edges[2] = Edge(this, p3, p1);

    //lets get longest Edge
    if(edges[0].getLength() > edges[1].getLength())
        long_edge = (edges[0].getLength() > edges[2].getLength())?0:2;
    else
        long_edge = (edges[1].getLength() > edges[2].getLength())?1:2;

    short_edge1 = (long_edge + 1) % 3;
    short_edge2 = (long_edge + 2) % 3;

    //let's include lighting
    WorldPoint normal = w1.getNormalizedNormalVector(w2,w3);

    float light_intensity = 0.5f * (float)(1+(game->light.getDirection() * normal));

    this->color.setBrightness(light_intensity);

}

void Triangle::draw()
{
    edges[long_edge].drawSpans(edges[short_edge1]);
    edges[long_edge].drawSpans(edges[short_edge2]);
}

