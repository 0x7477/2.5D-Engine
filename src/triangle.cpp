#include "triangle.hpp"
#include "game.hpp"
#include "colors.hpp"
#include <iostream>


Triangle::Triangle(Mesh* mesh, int p[3], int uv[3])
:screen{mesh->game->window_manager.screen}, texture{mesh->texture}
{

    auto screen_points = mesh->screen_points;
    auto world_points = mesh->world_points;
    auto uv_points = mesh->uv_points;

    WorldPoint normal = world_points[p[0]].getNormalizedNormalVector(world_points[p[1]],world_points[p[2]]);
    visible = mesh->game->player.isNormalVisible(normal);

    if(!visible) return;
    edges[0] = Edge(this, screen_points[p[0]], screen_points[p[1]], uv_points[uv[0]], uv_points[uv[1]]);
    edges[1] = Edge(this, screen_points[p[1]], screen_points[p[2]], uv_points[uv[1]], uv_points[uv[2]]);
    edges[2] = Edge(this, screen_points[p[2]], screen_points[p[0]], uv_points[uv[2]], uv_points[uv[0]]);

    //lets get longest Edge
    if(edges[0].getLength() > edges[1].getLength())
        long_edge = (edges[0].getLength() > edges[2].getLength())?0:2;
    else
        long_edge = (edges[1].getLength() > edges[2].getLength())?1:2;

    short_edge1 = (long_edge + 1) % 3;
    short_edge2 = (long_edge + 2) % 3;

    //let's include lighting

    light_intensity = 0.5f * (float)(1+(mesh->game->light.getDirection() * normal));
}

void Triangle::draw()
{
    if(!visible) return;
    edges[long_edge].drawSpans(edges[short_edge1]);
    edges[long_edge].drawSpans(edges[short_edge2]);
}

