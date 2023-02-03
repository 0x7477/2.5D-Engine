#include "game.hpp"
#include "colors.hpp"
#include "renderer.hpp"
#include <ctime>

#include <iostream>
#include <filesystem>

Game::Game(int argc, char **argv)
:map{50, 50}, renderer{this},window_manager{argc, argv, this} {};

void Game::start()
{
    readTextures("/home/kurt/Documents/DHBW/CG/resources");
    map.generate(this);

    billboards = {{{2,2,0},"test"},{{20,10,0},"nazi"},{{8,8,0},"nazi"}};
    last_clock = clock();

    Mesh cube{this,  {0xFF0000, 0xFF0000, 0xFF8000, 0xFF8000, 0xFFFF00, 0xFFFF00,  0x00FF00, 0x00FF00, 0x00FF80, 0x00FF80,0x00FFFF, 0x00FFFF, 0x0000FF, 0x0000FF, 0x000000, 0x000000 },{5,5,0.5}, Quaternion::identity,0.5, 
        {
            {1,1,-1}, {1,-1,-1}, {-1,1,-1},
            {-1,-1,-1}, {1,-1,-1}, {-1,1,-1},
            {1,1,1}, {-1,1,1}, {1,-1,1},
            {-1,-1,1}, {-1,1,1}, {1,-1,1},
            {1,-1,1}, {1,-1,-1}, {-1,-1,-1},
            {1,-1,1}, {-1,-1,-1}, {-1,-1,1},
            {1,1,1}, {1,1,-1}, {-1,1,-1},
            {1,1,1}, {-1,1,-1}, {-1,1,1},
            {1,-1,1}, {1,-1,-1}, {1,1,-1},
            {1,-1,1}, {1,1,1}, {1,1,-1},
            {-1,-1,1}, {-1,-1,-1}, {-1,1,-1},
            {-1,-1,1}, {-1,1,1}, {-1,1,-1},
        }
    };

    meshes.push_back(cube);


    Mesh triangle{this,  {0xFF0000},{3,3,0}, Quaternion::identity,1, {{-0.5,0,0}, {.5,0,0}, {0,0,0.5}}};

    meshes.push_back(triangle);


}

clock_t Game::updateDeltaClock()
{
    clock_t delta_time = clock() - last_clock;
    last_clock = clock();
    return delta_time;
}
void Game::update()
{
    auto delta_time = updateDeltaClock();
    player.move(&map, delta_time);

    renderer.render();
    window_manager.draw();

    meshes[0].rot = {0.000001 * clock(), 0.000001 * clock(),0.000001 * clock()};
    meshes[0].scale = 0.2 + 0.1*sin(0.000001 * clock());
    meshes[1].rot = {0,0, 0.000001 * clock()};
}

void Game::readTextures(std::string path)
{
    textures["test"] = Texture("");

    for (const auto &file : std::filesystem::recursive_directory_iterator(path))
    {
        std::string filename = file.path().filename();
        textures[filename.substr(0, filename.find('.'))] = Texture(file.path());
    }
}