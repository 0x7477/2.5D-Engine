#include "billboard.hpp"
#include "game.hpp"
#include <iostream>

Billboard::Billboard(double x, double y, std::string texture, double width, double height)
:x{x}, y{y}, width{width}, height{height}, texture{&(Game::textures[texture])}{}