#pragma once
#include "window_manager.hpp"
#include "screen.hpp"
#include "map.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "billboard.hpp"

#include <map>
#include <vector>
#include <string>

class Game
{
    public:
    Game(int argc, char** argv);

    void start();
    void readTextures(std::string path);
    void resize();
    void update();

    clock_t updateDeltaClock();
    static inline std::map<std::string, Texture> textures{};
    static inline std::vector<Billboard> objects{};
    clock_t last_clock;
    Player player;
    Map map;
    Renderer renderer;
    WindowManager window_manager;
};