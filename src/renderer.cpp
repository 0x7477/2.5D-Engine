#include "renderer.hpp"
#include "raycast.hpp"
#include "colors.hpp"
#include "game.hpp"
#include "mesh.hpp"

#include <iostream>
#include <cmath>

Renderer::Renderer(Game *game)
:game{game} {}



double Renderer::getRayAngle(int x)
{
    double minangle = game->player.angle - game->player.field_of_view / 2;
    return minangle + game->player.field_of_view * (double)x / (double)game->window_manager.screen->width;
}

int Renderer::getFloorScreenYPos(int screen_height, double distance)
{
    return (screen_height / 2) - (int)((screen_height / distance) * 1.3);
}

int Renderer::getCeilScreenYPos(int screen_height, double distance)
{
    return (screen_height / 2) + (int)((screen_height / distance) * 0.7);
}

double Renderer::getTextureSampleX(double ray_x, double ray_y)
{
    double sample_x = 0;

    double blockX = (double)((int)ray_x) + 0.5f;
    double blockY = (double)((int)ray_y) + 0.5f;

    double testAngle = atan2(ray_y - blockY, ray_x - blockX);

    //depending on which side of the wall we are we need to sample differently
    if (testAngle >= -M_PI * 0.25f && testAngle < M_PI * 0.25f)
        sample_x = ray_y - (int)ray_y;
    if (testAngle >= M_PI * 0.25f && testAngle < M_PI * 0.75f)
        sample_x = 1 - (ray_x - (int)ray_x);
    if (testAngle < -M_PI * 0.25f && testAngle >= -M_PI * 0.75f)
        sample_x = ray_x - (int)ray_x;
    if (testAngle >= M_PI * 0.75f || testAngle < -M_PI * 0.75f)
        sample_x = 1 - (ray_y - (int)ray_y);

    return sample_x;
}

void Renderer::renderWalls()
{
    auto screen = game->window_manager.screen;
    auto player = game->player;

    auto floor_texture = &Game::textures["floor"];

    double ray_x, ray_y;
    for (int x = 0; x < screen->width; x++)
    {
        const auto ray_angle = getRayAngle(x);
        const auto cos_ray_angle = std::cos(ray_angle);
        const auto sin_ray_angle = std::sin(ray_angle);
        const auto cos_angle_diff = std::cos(ray_angle-player.angle);
        
        //shoot the ray
        const auto distance = Raycast::raycast(&player, &game->map, ray_angle, &ray_x, &ray_y);

        const auto fish_eye_fixed_distance = distance *cos_angle_diff; 
        //calculate heights
        const int floor = getFloorScreenYPos(screen->height, fish_eye_fixed_distance);
        const int ceiling = getCeilScreenYPos(screen->height, fish_eye_fixed_distance);

        //get sample
        const double sample_x = getTextureSampleX(ray_x, ray_y);
        const auto texture = game->map((int)ray_x, (int)ray_y)->texture;

        for (int y = 0; y < screen->height; y++)
        {
            //check zBuffer
            if (distance > screen->getDepth(x, y))
                continue;

            Pixel color;
            if(y > ceiling)
            {
                const double z_plane = (0.7*screen->height) / (std::max(1.0,(double)(y-screen->height/2)) * cos_angle_diff);
                
                const auto plane_point_x = player.pos_x + sin_ray_angle * z_plane;
                const auto plane_point_y = player.pos_y + cos_ray_angle * z_plane;

                auto sample_x = plane_point_x - std::floor(plane_point_x);
                auto sample_y = plane_point_y - std::floor(plane_point_y);

                color = (*floor_texture)(sample_x,sample_y);
                color.setBrightness(1.0f- std::min((float)z_plane/32.0f,0.5f));
            }
            else if(y > floor)
            {
                //sample the y chord
                const double sample_y = (y - floor) / (double)(ceiling - floor);

                color = (*texture)(sample_x, sample_y);
                color.setBrightness(1.0f- std::min((float)distance/32.0f,0.5f));
            }
            else    //Floor
            {
                const double z_plane = (0.7*screen->height) / (std::max(1.0,(double)(screen->height/2-y)) * cos_angle_diff);
                
                const auto plane_point_x = player.pos_x + sin_ray_angle * z_plane;
                const auto plane_point_y = player.pos_y + cos_ray_angle * z_plane;

                auto sample_x = plane_point_x - std::floor(plane_point_x);
                auto sample_y = plane_point_y - std::floor(plane_point_y);

                color = (*floor_texture)(sample_x,sample_y);
                color.setBrightness(1.0f- std::min((float)z_plane/32.0f,0.5f));
            }


            //draw pixel
            screen->setColor(x, y, color);
            screen->setDepth(x, y, (float)distance);
        }
    }
}

void Renderer::renderBillboard(const Billboard& object)
{
    if (!object.isVisible(&game->player))
        return;

    auto screen = game->window_manager.screen;

    //get object information
    double dist = object.pos.getDistance(&game->player);

    int object_ceiling = getCeilScreenYPos(screen->height, dist);
    int object_floor = getFloorScreenYPos(screen->height, dist);

    int object_height = object_ceiling - object_floor;

    double object_ratio = object.height / object.width;
    double object_width = object_height / object_ratio;

    int object_center = (int)((0.5 * (object.pos.getAngle(&game->player) / (game->player.field_of_view / 2)) + 0.5) * screen->width);

    int texture_width = 64;
    int texture_height = 64;

    // loop through every pixel
    for (int lx = 0; lx < object_width; lx++)
    {
        int screen_x = object_center + lx - (int)(object_width / 2);

        //skip if not visible
        if (screen_x < 0 || screen_x >= screen->width)
            continue;

        //get sample of x chord
        int sample_x = (int)((lx / object_width) * texture_width);

        //loop through the heights
        for (int ly = 0; ly < object_height; ly++)
        {
            int screen_y = object_floor + ly;

            //skip if out of screen
            if (screen_y < 0 || screen_y >= screen->height)
                continue;


            int sample_y = (int)(((double)ly / object_height) * texture_height);

            Pixel sampled_pixel = (*object.texture)(sample_x, sample_y);

            //skip if texture is transparent at pixel
            if (sampled_pixel.a == 0)
                continue;

            //skip if billboard is hidden
            if (dist > screen->getDepth(screen_x, screen_y))
                continue;


            //draw pixel
            screen->setColor(screen_x, screen_y, sampled_pixel);
            screen->setDepth(screen_x, screen_y, (float)dist);
        }
    }
}


void Renderer::renderBillboards()
{
    for (const auto &object : game->billboards)
        renderBillboard(object);
}

double Renderer::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Renderer::renderMeshes()
{
    for(auto& mesh: game->meshes)
        mesh.draw();
}


void Renderer::render()
{
    game->window_manager.screen->fillZBuffer();
    renderWalls();
    renderBillboards();
    renderMeshes();
}