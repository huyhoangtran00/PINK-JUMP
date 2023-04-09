#pragma once
#include "Game.h"
#include "Object.h"
class Map
{
private:
    int gap;

public:
    Map();
    ~Map();
    Object platform[7];
    void draw(SDL_Renderer *gRenderer);
    void update();
    void loadMap(SDL_Renderer *gRenderer);
};