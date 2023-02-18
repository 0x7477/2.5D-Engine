#include "mesh.hpp"
#include "obj/obj.hpp"
#include "colors.hpp"


Mesh::Mesh(Game *game, std::string path, const Transform& transform)
:game{game},transform{transform},texture{Texture(path+"/uv.bmp")},obj{path+"/model.obj"} 
{
    world_points = std::vector<WorldPoint>{obj.vertexes.size()+1};
    screen_points = std::vector<ScreenPoint>{obj.vertexes.size()+1};
}

void Mesh::draw()
{
    for(std::size_t i = 0; i < obj.vertexes.size(); i++)
    {
        world_points[i]={transform.rot *  obj.vertexes[i].p * transform.scale + transform.pos};
        screen_points[i]={game, world_points[i]};   
    }


    for(const auto& face : obj.faces)
    {
        
        //apply transformations
        WorldPoint w1 = world_points[face.indices[0].vertex];
        WorldPoint w2 = world_points[face.indices[1].vertex];
        WorldPoint w3 = world_points[face.indices[2].vertex];

        //check visibility
        if(!game->player.isVisible(w1) && !game->player.isVisible(w2) && !game->player.isVisible(w3)) continue;

        
        //draw triangle
        Triangle{game,Color::white,w1,w2,w3}.draw();
    }
}