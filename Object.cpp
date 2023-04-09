#include "Object.h"

Object::Object()
{
    texture = NULL;
    rect = {0, 0, 0, 0};
}

Object::~Object()
{
    Free();
}

bool Object::LoadImg(string path, SDL_Renderer *gRenderer)
{
    Free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, 255, 0, 255));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, load_surface);
        if (newTexture != NULL)
        {
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        SDL_FreeSurface(load_surface);
    }
    texture = newTexture;
    return texture != NULL;
}

void Object::Render(SDL_Renderer *gRenderer, const SDL_Rect *clip)
{
    SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(gRenderer, texture, clip, &renderquad);
}

void Object::RenderEx(SDL_Renderer *gRenderer, const SDL_Rect *clip)

{
    SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopyEx(gRenderer, texture, clip, &renderquad, 0, NULL, SDL_FLIP_HORIZONTAL);
}

inline void Object::Free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}

bool Object::checkCollision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}
