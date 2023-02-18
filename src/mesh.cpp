#include "mesh.hpp"
#include "obj/obj.hpp"
#include "colors.hpp"

#include <iostream>
#include <filesystem>

std::string getUVName(std::string path)
{
    return std::filesystem::path(path).filename().string() + "_uv";
}

Mesh::Mesh(Game *game, std::string path, const Transform& transform)
:game{game},transform{transform},texture{&(Game::textures[getUVName(path)])},obj{path+"/model.obj"} 
{
    world_points = std::vector<WorldPoint>{obj.vertexes.size()};
    screen_points = std::vector<ScreenPoint>{obj.vertexes.size()};

    for(const auto & p: obj.texture_vertices)
        uv_points.push_back(p);
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
        
        int p[3]= {face.indices[0].vertex,face.indices[1].vertex,face.indices[2].vertex};
        int uvs[3]= {face.indices[0].vertexTexture, face.indices[1].vertexTexture, face.indices[2].vertexTexture};


        //apply transformations
        WorldPoint w1 = world_points[p[0]];
        WorldPoint w2 = world_points[p[1]];
        WorldPoint w3 = world_points[p[2]];

        //check visibility
        if(!game->player.isVisible(w1) && !game->player.isVisible(w2) && !game->player.isVisible(w3)) continue;

        //draw triangle

        Triangle{this,p, uvs}.draw();
    }
}