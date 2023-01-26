#include "renderer.hpp"
#include "raycast.hpp"
#include "colors.hpp"
#include "game.hpp"
#include "triangle.hpp"

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
    double sampleX = 0;

    double blockX = (double)((int)ray_x) + 0.5f;
    double blockY = (double)((int)ray_y) + 0.5f;

    double testAngle = atan2(ray_y - blockY, ray_x - blockX);

    if (testAngle >= -M_PI * 0.25f && testAngle < M_PI * 0.25f)
        sampleX = ray_y - (int)ray_y;
    if (testAngle >= M_PI * 0.25f && testAngle < M_PI * 0.75f)
        sampleX = 1 - (ray_x - (int)ray_x);
    if (testAngle < -M_PI * 0.25f && testAngle >= -M_PI * 0.75f)
        sampleX = ray_x - (int)ray_x;
    if (testAngle >= M_PI * 0.75f || testAngle < -M_PI * 0.75f)
        sampleX = 1 - (ray_y - (int)ray_y);

    return sampleX;
}

void Renderer::renderWalls()
{
    auto screen = game->window_manager.screen;
    int screen_height = screen->height;
    double ray_x, ray_y;
    for (int x = 0; x < screen->width; x++)
    {
        double distance = Raycast::raycast(&game->player, &game->map, getRayAngle(x), &ray_x, &ray_y);
        int floor = getFloorScreenYPos(screen_height, distance);
        int ceiling = getCeilScreenYPos(screen_height, distance);

        double sample_x = getTextureSampleX(ray_x, ray_y);

        for (int y = 0; y < screen->height; y++)
        {
            double sample_y = (y - floor) / (double)(ceiling - floor);

            int pixel_x = (int)(sample_x * 64);
            int pixel_y = (int)(sample_y * 64);

            Pixel sampled_pixel = (*game->map((int)ray_x, (int)ray_y)->texture)(pixel_x, pixel_y);

            screen->setColor(x, y, (y < ceiling && y > floor) ? sampled_pixel : Color::ceiling);
            screen->setDepth(x, y, (float)distance);
        }
    }
}

void Renderer::renderObjects()
{
    auto screen = game->window_manager.screen;
    int screen_height = screen->height;
    int screen_width = screen->width;

    for (auto &object : game->objects)
    {
        double dist_x = object.x - game->player.pos_x;
        double dist_y = object.x - game->player.pos_y;
        double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

        double object_angle = atan2(cos(game->player.angle), sin(game->player.angle)) - atan2(dist_y, dist_x);
        if (object_angle < -M_PI)
            object_angle += 2 * M_PI;
        else if (object_angle > M_PI)
            object_angle -= 2 * M_PI;

        bool visible = (fabs(object_angle) - fabs(atan2(dist, object.width / 2))) < game->player.field_of_view / 2;
        if (!visible)
            continue;

        int object_ceiling = getCeilScreenYPos(screen_height, dist);
        int object_floor = getFloorScreenYPos(screen_height, dist);

        int object_height = object_ceiling - object_floor;

        double object_ratio = object.height / object.width;
        double object_width = object_height / object_ratio;

        int objectcenter = (int)((0.5 * (object_angle / (game->player.field_of_view / 2)) + 0.5) * screen_width);

        int texture_width = 64;
        int texture_height = 64;

        for (int lx = 0; lx < object_width; lx++)
        {
            int screen_x = objectcenter + lx - (int)(object_width / 2);
            if (screen_x < 0 || screen_x >= screen_width)
                continue;

            int sampleX = (int)((lx / object_width) * texture_width);

            for (int ly = 0; ly < object_height; ly++)
            {
                int screen_y = object_floor + ly;
                if (screen_y < 0 || screen_y > screen_height)
                    continue;

                int sampleY = (int)(((double)ly / object_height) * texture_height);

                Pixel sampled_pixel = (*object.texture)(sampleX, sampleY);
                if (sampled_pixel.a == 0)
                    continue;

                if (dist > screen->getDepth(screen_x, screen_y))
                    continue;

                screen->setColor(screen_x, screen_y, sampled_pixel);
                screen->setDepth(screen_x, screen_y, (float)dist);
            }
        }
    }
}

double Renderer::map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Renderer::render()
{
    static double framecount = 0;
    game->window_manager.screen->fill(Color::black);
    renderWalls();
    renderObjects();

    double x_offset = sin(framecount) * 0.5;
    double y_offset = cos(framecount) * 0.5;

    ScreenPoint p1,p2,p3;
    for (int i = 0; i < 1; i++)
    {
        p1 = {game, {2.5 + i, 2.5, .5}};
        p2 = {game,{2.5 + x_offset + i, 2.5 + y_offset, 0}};
        p3 = {game,{2.5 - x_offset + i, 2.5 - y_offset, 0}};

        Triangle t(game->window_manager.screen, &Color::red, p1,p2,p3);
        t.draw();
    }

    framecount += 0.01;
}