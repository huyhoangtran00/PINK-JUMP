#pragma once
#include "Game.h"

class Object
{
public:
    Object();
    ~Object();
    void SetRect(const int &x, const int &y) { rect.x = x, rect.y = y; }
    SDL_Rect GetRect() const { return rect; }
    SDL_Texture *GetTexture() const { return texture; }

    bool LoadImg(string path, SDL_Renderer *gRenderer);
    void Render(SDL_Renderer *gRenderer, const SDL_Rect *clip = NULL);
    void RenderEx(SDL_Renderer *gRenderer, const SDL_Rect *clip = NULL);
    bool loadText(string textureText, SDL_Color textColor, TTF_Font *gFont, SDL_Renderer *gRenderer);
    void Free();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    SDL_Texture *texture;
    SDL_Rect rect;
};