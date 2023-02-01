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

    objects = {{2,2,"test"},{20,10,"nazi"},{8,8,"nazi"}};
    last_clock = clock();
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