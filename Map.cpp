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
        platform[i].rect.y += 2;
        platform[i].Render(gRenderer, NULL);
        if (platform[i].rect.y > SCREEN_HEIGHT)
        {
            platform[i].rect.x = rand() % SCREEN_WIDTH + 0;
            platform[i].rect.y = 0;
        }
        if (i == 2 || i == 5)
        {
            if (platform[i].rect.x < SCREEN_WIDTH / 4)
            {
                platform[i].rect.x++;
            }
            if (platform[i].rect.x > SCREEN_WIDTH * 3 / 4)
            {
                platform[i].rect.x--;
            }
        }
    }
}
