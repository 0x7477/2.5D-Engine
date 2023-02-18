#include "triangle.hpp"
#include "game.hpp"
#include "colors.hpp"
#include <iostream>


Triangle::Triangle(Mesh* mesh, int p1, int p2, int p3)
:screen{mesh->game->window_manager.screen}, color{Color::white}
{
    auto screen_points = mesh->screen_points;

    edges[0] = Edge(this, screen_points[p1], screen_points[p2]);
    edges[1] = Edge(this, screen_points[p2], screen_points[p3]);
    edges[2] = Edge(this, screen_points[p3], screen_points[p1]);

    //lets get longest Edge
    if(edges[0].getLength() > edges[1].getLength())
        long_edge = (edges[0].getLength() > edges[2].getLength())?0:2;
    else
        long_edge = (edges[1].getLength() > edges[2].getLength())?1:2;

    short_edge1 = (long_edge + 1) % 3;
    short_edge2 = (long_edge + 2) % 3;

    //let's include lighting
    // WorldPoint normal = w1.getNormalizedNormalVector(w2,w3);

    // float light_intensity = 0.5f * (float)(1+(game->light.getDirection() * normal));

    // this->color.setBrightness(light_intensity);
}

void Triangle::draw()
{
    edges[long_edge].drawSpans(edges[short_edge1]);
    edges[long_edge].drawSpans(edges[short_edge2]);
}

