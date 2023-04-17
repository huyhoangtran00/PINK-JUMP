#include "Map.h"

Map::Map()
{
    gap = SCREEN_HEIGHT / 7;
    for (int i = 0; i < 7; i++)
    {
        platform[i].rect = {rand() % SCREEN_WIDTH - 100 + 100, gap * i, 300, 100};
    }
}

Map::~Map()
{
    platform->Free();
}

void Map::loadMap(SDL_Renderer *gRenderer)
{

    for (int i = 0; i < 7; i++)
    {
        platform[i].LoadImg("img/cloud.png", gRenderer);
        platform[i].rect.h = 40;
        platform[i].rect.w = 100;
    }
}

void Map::draw(SDL_Renderer *gRenderer)
{
    for (int i = 0; i < 7; i++)
    {

        platform[i].Render(gRenderer, NULL);
    }
}
