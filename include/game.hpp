#pragma once
#include "window_manager.hpp"
#include "screen.hpp"
#include "map.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "billboard.hpp"
#include "mesh.hpp"
#include "directional_light.hpp"

#include <map>
#include <vector>
#include <string>

/// @brief The Game Object
class Game
{
    public:
    Game(int argc, char** argv);

    /// @brief game setup loop
    void start();
    /// @brief read textures from file
    /// @param path the path to the textures foldee
    void readTextures(std::string path);
    /// @brief the game loop function 
    void update();

    /// @brief updates the games update delta
    /// @return returns delta time
    clock_t updateDeltaClock();

    /// @brief the games textures
    static inline std::map<std::string, Texture> textures{};
    /// @brief teh games billboard objects
    static inline std::vector<Billboard> billboards{};
    /// @brief the games meshes
    static inline std::vector<Mesh> meshes{};
    /// @brief the last clock timestamp
    clock_t last_clock;
    /// @brief the player object of the game
    Player player;
    /// @brief the game's map
    Map map;
    /// @brief The renderer for the game
    Renderer renderer;
    /// @brief the light for lighting up the game
    DirectionalLight light{{0.5773502691896258,-0.5773502691896258,0.5773502691896258},1};
    /// @brief the window manager for the game
    WindowManager window_manager;
};