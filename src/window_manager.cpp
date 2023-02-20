#include "window_manager.hpp"
#include "colors.hpp"
#include "game.hpp"
#include <GL/freeglut.h>
#include <iostream>

int WindowManager::window_height = 600;
int WindowManager::window_width = 1000;

int factor = 2; //how many pixels per pixel you want to display
Game *WindowManager::game;
WindowManager::WindowManager(int argc, char **argv, Game *game)
{
    //init screen
    screen = new Screen(window_width / factor, window_height / factor);

    //assign static variable
    WindowManager::game = game;

    //setup window
    glutInit(&argc, argv);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(window_width, window_height);
    glutInitDisplayMode(GLUT_RGBA);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
    glutCreateWindow("shooter");

    //used for a more older look
    glPixelZoom(factor, factor);

    glutIgnoreKeyRepeat(1);   // ignore annoying key repeat delay

    // set function pointers
    glutIdleFunc(update);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey); 

    // init game
    game->start();

    // enter update loop
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

void WindowManager::close()
{
    glutLeaveMainLoop();
}


void WindowManager::reshape(int width, int height)
{
    //create a new screen buffer
    window_width = width / factor;
    window_height = height / factor;
    delete screen;
    screen = new Screen(window_width, window_height);
}