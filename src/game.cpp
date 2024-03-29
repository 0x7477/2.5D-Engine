#include "game.hpp"
#include "colors.hpp"
#include "renderer.hpp"
#include "transform.hpp"
#include <ctime>

#include <iostream>
#include <filesystem>

Game::Game(int argc, char **argv)
:map{50, 50}, renderer{this},window_manager{argc, argv, this} 
{};

void Game::start()
{
    //setup the games ressources
    readTextures("resources/");
    map.generate();

    // create some billboards
    billboards = {
        {{2,2,0},"test"},
        {{22,12,0},"tomato"},
        {{8,8,0},"tomato_rambo"},
        {{22,22,0},"tomato_back"},
        {{25,30,-0.2},"tree",2,3},
        {{45,32,-0.2},"tree",2,3}
        };

    //init gameclock
    last_clock = clock();


    Mesh dice{this, "resources/models/dice",{{5,5,0.5}, Quaternion::identity,0.5}};
    meshes.push_back(dice);

    Mesh roof{this, "resources/models/roof",{{15,15,1}, {M_PI/2,0,0},5}};
    meshes.push_back(roof);



    // Mesh cube2{this, "/home/kurt/Desktop/untitled.obj",{0xFF0000, 0xFF0000, 0xFF8000, 0xFF8000, 0xFFFF00, 0xFFFF00,  0x00FF00, 0x00FF00, 0x00FF80, 0x00FF80,0x00FFFF, 0x00FFFF, 0x0000FF, 0x0000FF, 0x000000, 0x000000,0xFF0000, 0xFF0000, 0xFF8000, 0xFF8000, 0xFFFF00, 0xFFFF00,  0x00FF00, 0x00FF00, 0x00FF80, 0x00FF80,0x00FFFF, 0x00FFFF, 0x0000FF, 0x0000FF, 0x000000, 0x000000 },{5,5,0.5}, Quaternion::identity,0.5};
    // meshes.push_back(cube2);

    // //add cube to the scene
    // Mesh cube{this,  {0xFF0000, 0xFF0000, 0xFF8000, 0xFF8000, 0xFFFF00, 0xFFFF00,  0x00FF00, 0x00FF00, 0x00FF80, 0x00FF80,0x00FFFF, 0x00FFFF, 0x0000FF, 0x0000FF, 0x000000, 0x000000 },{5,5,0.5}, Quaternion::identity,0.5, 
    //     {
    //         {1,1,-1}, {1,-1,-1}, {-1,1,-1},
    //         {-1,-1,-1}, {1,-1,-1}, {-1,1,-1},
    //         {1,1,1}, {-1,1,1}, {1,-1,1},
    //         {-1,-1,1}, {-1,1,1}, {1,-1,1},
    //         {1,-1,1}, {1,-1,-1}, {-1,-1,-1},
    //         {1,-1,1}, {-1,-1,-1}, {-1,-1,1},
    //         {1,1,1}, {1,1,-1}, {-1,1,-1},
    //         {1,1,1}, {-1,1,-1}, {-1,1,1},
    //         {1,-1,1}, {1,-1,-1}, {1,1,-1},
    //         {1,-1,1}, {1,1,1}, {1,1,-1},
    //         {-1,-1,1}, {-1,-1,-1}, {-1,1,-1},
    //         {-1,-1,1}, {-1,1,1}, {-1,1,-1},
    //     }
    // };

    // // meshes.push_back(cube);

    // // add traingle to the game
    // Mesh triangle{this,  {0xFF0000},{3,3,0}, Quaternion::identity,1, {{-0.5,0,0}, {.5,0,0}, {0,0,0.5}}};

    // meshes.push_back(triangle);


}

clock_t Game::updateDeltaClock()
{
    clock_t delta_time = clock() - last_clock;
    last_clock = clock();
    return delta_time;
}
void Game::update()
{
    //get delta time
    auto delta_time = updateDeltaClock();

    //move player
    player.move(&map, delta_time);
    //render scene
    renderer.render();

    //draw rendered image to window
    window_manager.draw();

    //transform objects
    meshes[0].transform.rot = {0.000001 * clock(), 0.000001 * clock(),0.000001 * clock()};
    meshes[0].transform.scale = 0.2 + 0.1*sin(0.000001 * clock());
}

void Game::readTextures(std::string path)
{
    if(!std::filesystem::exists(path)) 
    {
        std::cout << "no textures found at path: " << path << "\n";   
        return;
    }    

    textures["test"] = Texture();

    for (const auto &file : std::filesystem::recursive_directory_iterator(path))
    {
        if(file.path().extension() != ".bmp") continue;

        std::string filename = file.path().filename();

        textures[filename.substr(0, filename.find('.'))] = Texture(file.path());
    }

}