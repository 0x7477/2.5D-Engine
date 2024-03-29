#pragma once
#include <tuple>
class Game;
class Texture;
class Mesh;
class Screen;
class Player;
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
    static int getFloorScreenYPos(const int& screen_height, const double& distance);
    /// @brief get the height of the ceil
    /// @param screen_height height of the screen
    /// @param distance the distance to a point
    /// @return ceil of the floor
    static int getCeilScreenYPos(const int& screen_height, const double& distance);


    /// @brief maps a value linear
    /// @return the linear mapped value
    static double map(const double& x, const double& in_min, const double& in_max, const double& out_min, const double& out_max);


    /// @brief get the angle of the ray shot from pixel x
    /// @param x the pixel
    /// @return the angle at pixel x
    double getRayAngle(const int& x);

    /// @brief get the x choordinate of the ray hit
    /// @param ray_x the rays hit at x pos
    /// @param ray_y the rays hit at y pos
    /// @return the textures x choordinate at hit (0-1)
std::tuple<std::size_t, double> getTextureSampleX(const double &ray_x, const double &ray_y);
    std::tuple<std::size_t,double> getSkyboxSampleX(double angle);


    /// @brief render all the billboards
    void renderBillboards();

    /// @brief render a Billboard
    /// @param object teh billboard to be rendered
    void renderBillboard(const Billboard& object);


void renderBillboardColumn(const Billboard &object, const int& x, const int& object_center, const double& object_width,const int& object_height, const int &object_floor, const int &unit_height, const double& dist);
void renderBillboardPixel(const Billboard &object, const int& screen_x,const int& y, const int& object_center, const double& object_width,const int& object_height, const int &object_floor, const int &unit_height, const double& dist,const double& sample_x);

    /// @brief render all the meshes contained in the game
    void renderMeshes();


    /// @brief render the walls of the game
    void renderWalls();


    inline void renderWallColumn(const std::size_t &x);
    inline void renderSkybox(const std::size_t &x,const std::size_t &y,const std::size_t & sky_image,const double & sky_sample_x);
    inline bool renderCeiling(const std::size_t &x,const std::size_t &y,const double & cos_ray_angle,const double & sin_ray_angle,const double & cos_angle_diff);
    inline bool renderWall(const std::size_t &x, const std::size_t &y, const double& distance, const int &floor, const int &ceiling, const Texture* texture, const double& sample_x,const int& wall_side);
    inline bool renderFloor(const std::size_t &x, const std::size_t &y, const double &cos_ray_angle, const double &sin_ray_angle, const double &cos_angle_diff);
    inline void renderWallPixel(const int &x,const int &y,const double & cos_ray_angle,const double & sin_ray_angle,const double & cos_angle_diff,const double& distance, const int &floor, const int &ceiling, const Texture* texture, const double& sample_x,const int& wall_side,const std::size_t & sky_image,const double & sky_sample_x);

    Game* game;
    Screen* screen;
    Player* player;
    float wall_lightings[4];

    Texture *sky_textures[6];
};