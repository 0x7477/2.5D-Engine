#pragma once
#include "point.hpp"
class Game;
class Mesh;
class Billboard;

/// @brief The game renderer
class Renderer
{
public:
    Renderer(Game* game);
    /// @brief Render the game
    void render();

    /// @brief get the height of the floor
    /// @param screen_height height of the screen
    /// @param distance the distance to a point
    /// @return height of the floor
    static int getFloorScreenYPos(int screen_height, double distance);
    /// @brief get the height of the ceil
    /// @param screen_height height of the screen
    /// @param distance the distance to a point
    /// @return ceil of the floor
    static int getCeilScreenYPos(int screen_height, double distance);


    /// @brief maps a value linear
    /// @return the linear mapped value
    static double map(double x, double in_min, double in_max, double out_min, double out_max);


    /// @brief get the angle of the ray shot from pixel x
    /// @param x the pixel
    /// @return the angle at pixel x
    double getRayAngle(int x);

    /// @brief get the x choordinate of the ray hit
    /// @param ray_x the rays hit at x pos
    /// @param ray_y the rays hit at y pos
    /// @return the textures x choordinate at hit (0-1)
    double getTextureSampleX(double ray_x, double ray_y);


    /// @brief render all the billboards
    void renderBillboards();

    /// @brief render a Billboard
    /// @param object teh billboard to be rendered
    void renderBillboard(const Billboard& object);

    /// @brief render all the meshes contained in the game
    void renderMeshes();


    /// @brief render the walls of the game
    void renderWalls();

    Game* game;
};