#include "window_manager.hpp"
#include "settings.hpp"
#include "colors.hpp"
#include "game.hpp"
#include <GL/freeglut.h>
#include <iostream>

int WindowManager::window_height = 600;
int WindowManager::window_width = 1000;

int factor = 1;
Game *WindowManager::game;
WindowManager::WindowManager(int argc, char **argv, Game *game)
{
    screen = new Screen(window_width / factor, window_height / factor);
    WindowManager::game = game;

    glutInit(&argc, argv);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("shooter");
    glPixelZoom(factor, factor);

    glutIgnoreKeyRepeat(1);   // ignore annoying windows key repeat delay
    glutIdleFunc(update);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey); 
    // OpenGL initialisation

    game->start();

    // enter glut event processing infinite loop
    glutMainLoop();
}

void WindowManager::start()
{
    game->start();
}

void WindowManager::draw()
{
    glDrawPixels(screen->width, screen->height, GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte *)screen->buffer);
    glFlush();
}

void WindowManager::pressKey(unsigned char key, int xx, int yy)
{
    if (key == 27)
        exit(0);
    buttons[key] = true;
}

void WindowManager::releaseKey(unsigned char key, int xx, int yy)
{
    buttons[key] = false;
}

void WindowManager::update()
{
    game->update();
}

void WindowManager::reshape(int width, int height)
{
    window_width = width / factor;
    window_height = height / factor;
    delete screen;
    screen = new Screen(window_width, window_height);
}