#include "renderer.hpp"
#include "raycast.hpp"
#include "colors.hpp"
#include "game.hpp"
#include "mesh.hpp"

#include <iostream>
#include <tuple>
#include <cmath>

Renderer::Renderer(Game *game)
    : game{game}, player{&game->player},
      sky_textures{&Game::textures["sky_0"], &Game::textures["sky_1"], &Game::textures["sky_2"], &Game::textures["sky_3"], &Game::textures["test"], &Game::textures["swastika"]}

{
}

double Renderer::getRayAngle(const int &x)
{
    const double minangle = game->player.angle - game->player.field_of_view / 2;
    return Renderer::map(x, 0, game->window_manager.screen->width, minangle, minangle + game->player.field_of_view);
}

int Renderer::getFloorScreenYPos(const int &screen_height, const double &distance)
{
    return (screen_height / 2) - (int)((screen_height / distance) * 1.3);
}

int Renderer::getCeilScreenYPos(const int &screen_height, const double &distance)
{
    return (screen_height / 2) + (int)((screen_height / distance) * 0.7);
}

double Renderer::getTextureSampleX(const double &ray_x, const double &ray_y)
{
    double blockX = (double)((int)ray_x) + 0.5f;
    double blockY = (double)((int)ray_y) + 0.5f;

    double testAngle = atan2(ray_y - blockY, ray_x - blockX);

    double sample_x = 0;
    // depending on which side of the wall we are we need to sample differently
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

std::tuple<int, double> Renderer::getSkyboxSampleX(double angle)
{
    angle -= floor(angle / (2 * M_PI)) * 2 * M_PI;

    double percent = 4 * angle / (2 * M_PI);

    if (percent < 0.5)
        return {0, Renderer::map(percent, 0.0, 0.5, 0.5, 1.0)};
    if (percent < 1.5)
        return {2, Renderer::map(percent, 0.5, 1.5, 0.0, 1.0)};
    if (percent < 2.5)
        return {1, Renderer::map(percent, 1.5, 2.5, 0.0, 1.0)};
    if (percent < 3.5)
        return {3, Renderer::map(percent, 2.5, 3.5, 0.0, 1.0)};

    return {0, Renderer::map(percent, 3.5, 4.0, 0.0, 0.5)};
}

void Renderer::renderSkybox(const int &x, const int &y, const int &sky_image, const double &sky_sample_x)
{
    if (screen->getDepth(x, y) != __FLT_MAX__)
        return;

    Pixel color;
    if (y > screen->height / 2)
    {
        double sample_y = (double)y / (double)screen->height;
        color = (*(sky_textures[sky_image]))(sky_sample_x, sample_y);
    }
    else
    {
        color = Color::green;
    }
    screen->setColor(x, y, color);
}

bool Renderer::renderFloor(const int &x, const int &y, const double &cos_ray_angle, const double &sin_ray_angle, const double &cos_angle_diff)
{

    const double z_plane = (1.3 * screen->height) / (std::max(1.0, (double)(screen->height / 2 - y)) * cos_angle_diff);

    const auto plane_point_x = player->pos_x + sin_ray_angle * z_plane;
    const auto plane_point_y = player->pos_y + cos_ray_angle * z_plane;

    const int sample_x_int = (int)std::floor(plane_point_x);
    const int sample_y_int = (int)std::floor(plane_point_y);

    auto ceil_tile = game->map(sample_x_int, sample_y_int);

    if (!game->map.covers(sample_x_int, sample_y_int))
        return false;

    if (ceil_tile->ceiling_transparent)
        return false;

    auto sample_x = plane_point_x - sample_x_int;
    auto sample_y = plane_point_y - sample_y_int;

    screen->setDepth(x, y, (float)z_plane);

    const auto floor_texture = game->map(sample_x_int, sample_y_int)->floor_texture;
    screen->setColor(x, y, (*floor_texture)(sample_x, sample_y));

    return true;
}

bool Renderer::renderCeiling(const int &x, const int &y, const double &cos_ray_angle, const double &sin_ray_angle, const double &cos_angle_diff)
{
    const double z_plane = (0.7 * screen->height) / (std::max(1.0, (double)(y - screen->height / 2)) * cos_angle_diff);

    const auto plane_point_x = player->pos_x + sin_ray_angle * z_plane;
    const auto plane_point_y = player->pos_y + cos_ray_angle * z_plane;

    const int sample_x_int = (int)std::floor(plane_point_x);
    const int sample_y_int = (int)std::floor(plane_point_y);

    if (!game->map.covers(sample_x_int, sample_y_int))
        return false;

    auto ceil_tile = game->map(sample_x_int, sample_y_int);

    if (ceil_tile->ceiling_transparent)
        return false;

    auto sample_x = plane_point_x - sample_x_int;
    auto sample_y = plane_point_y - sample_y_int;

    const auto ceiling_texture = game->map(sample_x_int, sample_y_int)->ceiling_texture;
    screen->setColor(x, y, (*ceiling_texture)(sample_x, sample_y));
    screen->setDepth(x, y, (float)z_plane);

    return true;
}

bool Renderer::renderWall(const int &x, const int &y, const double &distance, const int &floor, const int &ceiling, const Texture *texture, const double &sample_x)
{
    // sample the y chord
    const double sample_y = (y - floor) / (double)(ceiling - floor);

    Pixel sample = (*texture)(sample_x, sample_y);
    if (sample.a == 0)
        return false;

    screen->setDepth(x, y, (float)distance);
    screen->setColor(x, y, sample);

    return true;
}

void Renderer::renderWallCollum(const int &x)
{
    auto player = game->player;

    const auto ray_angle = getRayAngle(x);
    const auto cos_ray_angle = std::cos(ray_angle);
    const auto sin_ray_angle = std::sin(ray_angle);
    const auto cos_angle_diff = std::cos(ray_angle - player.angle);

    // shoot the ray
    double ray_x, ray_y;
    const auto distance = Raycast::raycast(&player, &game->map, ray_angle, &ray_x, &ray_y);

    const auto fish_eye_fixed_distance = distance * ((WindowManager::buttons['b']) ? 1 : cos_angle_diff);
    // calculate heights
    const int floor = getFloorScreenYPos(screen->height, fish_eye_fixed_distance);
    const int ceiling = getCeilScreenYPos(screen->height, fish_eye_fixed_distance);

    // get sample
    const double sample_x = getTextureSampleX(ray_x, ray_y);
    const auto texture = game->map((int)ray_x, (int)ray_y)->texture;

    int sky_image = 0;
    double sky_sample_x = 0;

    std::tie(sky_image, sky_sample_x) = getSkyboxSampleX(ray_angle);

    for (int y = 0; y < screen->height; y++)
    {
        bool rendered = false;
        // renderSkybox

        if (y >= ceiling) // draw a roof tile
        {
            rendered = renderCeiling(x, y, cos_ray_angle, sin_ray_angle, cos_angle_diff);
        }
        else if (y >= floor)
        {
            rendered = renderWall(x, y, distance, floor, ceiling, texture, sample_x);
        }
        else // Floor
        {
            rendered = renderFloor(x, y, cos_ray_angle, sin_ray_angle, cos_angle_diff);
        }

        if (!rendered)
            renderSkybox(x, y, sky_image, sky_sample_x);
    }
}

void Renderer::renderWalls()
{
    for (int x = 0; x < game->window_manager.screen->width; x++)
        renderWallCollum(x);
}

void Renderer::renderBillboard(const Billboard &object)
{
    if (!object.isVisible(&game->player))
        return;

    auto screen = game->window_manager.screen;

    // get object information
    double dist = object.pos.getDistance(&game->player);

    int object_ceiling = getCeilScreenYPos(screen->height, dist);
    int object_floor = getFloorScreenYPos(screen->height, dist);

    int unit_height = object_ceiling - object_floor;
    int object_height = (int)(unit_height * object.height);

    double object_ratio = object.height / object.width;
    double object_width = object_height / object_ratio;

    int object_center = (int)((0.5 * (object.pos.getAngle(&game->player) / (game->player.field_of_view / 2)) + 0.5) * screen->width);

    int texture_width = object.texture->width;
    int texture_height = object.texture->height;

    // loop through every pixel
    for (int lx = 0; lx < object_width; lx++)
    {
        int screen_x = object_center + lx - (int)(object_width / 2);

        // skip if not visible
        if (screen_x < 0 || screen_x >= screen->width)
            continue;

        // get sample of x chord
        int sample_x = (int)((lx / object_width) * texture_width);

        // loop through the heights
        for (int ly = 0; ly < object_height; ly++)
        {
            int screen_y = object_floor + ly + (int)(unit_height * object.pos.z);
            // skip if out of screen
            if (screen_y < 0 || screen_y >= screen->height)
                continue;

            int sample_y = (int)(((double)ly / object_height) * texture_height);

            Pixel sampled_pixel = (*object.texture)(sample_x, sample_y);

            // skip if texture is transparent at pixel
            if (sampled_pixel.a == 0)
                continue;

            // skip if billboard is hidden
            if (dist > screen->getDepth(screen_x, screen_y))
                continue;

            // draw pixel
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

double Renderer::map(const double &x, const double &in_min, const double &in_max, const double &out_min, const double &out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Renderer::renderMeshes()
{
    for (auto &mesh : game->meshes)
    {
        mesh.draw();
    }
}

void Renderer::render()
{
    screen = game->window_manager.screen; // update in case we have gotten a new screen buffer
    game->window_manager.screen->fillZBuffer();
    renderMeshes();
    renderWalls();
    renderBillboards();
}