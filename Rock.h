#pragma once
#include "Game.h"
#include "Object.h"

class Rock : public Object
{
public:
    Rock();
    ~Rock();
    void draw(SDL_Renderer *gRenderer);
    void update(SDL_Rect rect_player);
    void loadRock(SDL_Renderer *gRenderer);
    Object rock[2];

private:
    SDL_Rect rock_rect[60];
    int ampha;
    int vx;
    int vy;
    int cnt;
};