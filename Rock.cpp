#include "Rock.h"
Rock::Rock()
{
    cnt = 0;
    ampha = rand() % 180 + 0;
    for (int i = 0; i < 2; i++)
    {
        rock[i].rect.y = rand() % 500 + 0;
        rock[i].rect.x = rand() % SCREEN_WIDTH + 0;
    }
}
Rock::~Rock()
{
    Free();
    rock[0].Free();
    rock[1].Free();
}

void Rock::draw(SDL_Renderer *gRenderer)
{
    for (int i = 0; i < 2; i++)
    {
        rock[i].rect.h = 80;
        rock[i].rect.w = 40;
        int frame = cnt;
        rock[i].Render(gRenderer, &rock_rect[frame]);

        cnt++;
        if (frame >= 60)
            cnt = 0;
    }
    // SDL_RenderFillRect(gRenderer, &rock[1].rect);
}

void Rock::update(SDL_Rect rect_player)
{

    for (int i = 0; i < 2; i++)
    {

        if (rock[i].rect.y > SCREEN_HEIGHT)
        {
            rock[i].rect.x = rand() % SCREEN_WIDTH;
            rock[i].rect.y = 0;
        }
    }

    rock[0].rect.y += 10;

    rock[1].rect.y += 15;
}
void Rock::loadRock(SDL_Renderer *gRenderer)
{
    for (int i = 0; i < 2; i++)
        rock[i].LoadImg("img/rock.png", gRenderer);

    int x = 0;
    int y = 0;
    for (int i = 0; i < 60; i++)
    {
        rock_rect[i] = {x, y, 10, 26};
        x += 10;
        if (x >= 100)
        {
            x = 0;
            y += 26;
        }
    }
}