#pragma once
#include "Game.h"
#include "Object.h"

class Menu
{
private:
    Object play_crr;
    Object play[2];

    Object exit;
    SDL_Rect exit_rect[2];

public:
    Menu();
    ~Menu();
    void draw(SDL_Renderer *gRenderer);
    void check_mouse(SDL_Event event, bool &quit);
    void load(SDL_Renderer *gRenderer);
    void Exit(SDL_Event event, bool &quit, bool &QUIT);
    void drawExit(SDL_Renderer *gRenderer);
};
