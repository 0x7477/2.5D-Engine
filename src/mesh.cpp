#include "mesh.hpp"
#include "obj/obj.hpp"


Mesh::Mesh(Game* game, std::vector<Pixel> colors, const WorldPoint& pos,const Quaternion& rot,  double scale , std::vector<WorldPoint> vertices)
:game{game},pos{pos},rot{rot},scale{scale}, colors{colors},vertices{vertices}{};




Mesh::Mesh(Game *game, std::string path,std::vector<Pixel> colors, const WorldPoint &pos,const Quaternion& rot, double scale)
:game{game},pos{pos},rot{rot},scale{scale},colors{colors},vertices{OBJ::loadOBJ(path)}
{

}

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

        //draw triangle
        Triangle{game, colors[i],w1,w2,w3}.draw();
    }
}