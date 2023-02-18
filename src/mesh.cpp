#include "mesh.hpp"
#include "obj/obj.hpp"


Mesh::Mesh(Game* game, std::vector<Pixel> colors, const Transform& transform, std::vector<WorldPoint> vertices)
:game{game},transform{transform},colors{colors},vertices{vertices}{};




Mesh::Mesh(Game *game, std::string path,std::vector<Pixel> colors, const Transform& transform)
:game{game},transform{transform},colors{colors},vertices{OBJ::loadOBJ(path)} {}

void Mesh::draw() const
{
    for(std::size_t i = 0; 3*i < vertices.size(); i ++)
    {
        //apply transformations
        WorldPoint w1{transform.rot * vertices[3*i]   * transform.scale + transform.pos};
        WorldPoint w2{transform.rot * vertices[3*i+1] * transform.scale + transform.pos};
        WorldPoint w3{transform.rot * vertices[3*i+2] * transform.scale + transform.pos};

        //check visibility
        if(!game->player.isVisible(w1) && !game->player.isVisible(w2) && !game->player.isVisible(w3)) continue;

        //draw triangle
        Triangle{game, colors[i],w1,w2,w3}.draw();
    }
}