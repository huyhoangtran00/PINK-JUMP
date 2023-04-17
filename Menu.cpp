#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::check_mouse(SDL_Event event, bool &quit)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < play_crr.rect.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > play_crr.rect.x + MENU_PLAY_W)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < play_crr.rect.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > play_crr.rect.y + MENU_PLAY_H)
        {
            inside = false;
        }

        if (inside)
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                play_crr = play[1];
                break;

            case SDL_MOUSEBUTTONDOWN:
                quit = true;
                break;

                // case SDL_MOUSEBUTTONUP:
                //     mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                //     break;
            }
        }
        else
        {
            play_crr = play[0];
        }
    }
}

void Menu::draw(SDL_Renderer *gRenderer)
{
    play_crr.rect = {SCREEN_WIDTH / 2 - MENU_PLAY_W / 2, SCREEN_HEIGHT / 2 - MENU_PLAY_H / 2, MENU_PLAY_W, MENU_PLAY_H};
    play_crr.Render(gRenderer, NULL);
}

void Menu::load(SDL_Renderer *gRenderer)
{
    play[0].LoadImg("img/hoang1.png", gRenderer);
    play[1].LoadImg("img/hoang2.png", gRenderer);
    play_crr = play[0];
    exit.LoadImg("img/exit.png", gRenderer);
}

void Menu::Exit(SDL_Event event, bool &quit, bool &QUIT)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Check if mouse is in button
        bool inside = true;

        // Mouse is left of the button
        if (x < exit.rect.x)
        {
            inside = false;
        }
        // Mouse is right of the button
        else if (x > exit.rect.x + 100)
        {
            inside = false;
        }
        // Mouse above the button
        else if (y < exit.rect.y)
        {
            inside = false;
        }
        // Mouse below the button
        else if (y > exit.rect.y + 100)
        {
            inside = false;
        }

        if (inside)
        {
            switch (event.type)
            {

            case SDL_MOUSEBUTTONDOWN:
            {
                QUIT = false;
                quit = true;
            }
            }
        }
    }
}

void Menu::drawExit(SDL_Renderer *gRenderer)
{
    exit.rect.w = 100;
    exit.rect.h = 100;
    exit.rect.x = SCREEN_WIDTH / 2 - exit.rect.w / 2;
    exit.rect.y = SCREEN_HEIGHT / 2 + 50;
    exit.Render(gRenderer, NULL);
}