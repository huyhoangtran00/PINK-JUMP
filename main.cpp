#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Rock.h"
#include "Map.h"
#include "Menu.h"

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
Mix_Music *gMusic = NULL;
SDL_Event event;
Object background;
Rock rock;
Map map;
Player player(map.platform);
Menu menu;
int volume;
bool init();
void loadMedia();
void free();
int main(int argc, char *argv[])
{
    if (!init())
        return -1;
    bool quit = false;
    bool quitMenu = false;

    loadMedia();
    // srand(time(0)); // set initial seed value to system clock

    while (!quitMenu)
    {
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);
        if (Mix_PlayingMusic() == 0)
        {
            // Play the music
            Mix_PlayMusic(gMusic, -1);
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quitMenu = true;
                quit = true;
            }
            menu.check_mouse(event, quitMenu);
        }
        background.Render(gRenderer);
        menu.draw(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    while (!quit)
    {
        if (Mix_PlayingMusic() == 0)
        {
            // Play the music
            Mix_PlayMusic(gMusic, -1);
        }
        // If there is no music playing

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            player.handleEvent(event);
        }
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        player.update(map.platform, rock.rock);
        rock.update(player.rect);
        background.Render(gRenderer);
        player.draw(gRenderer, quit);
        map.draw(gRenderer);

        rock.draw(gRenderer);
        SDL_Delay(30);
        SDL_RenderPresent(gRenderer);
    }
    free();
    return 0;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("Game Doudle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
                // Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void loadMedia()
{

    // Load music
    menu.load(gRenderer);
    gMusic = Mix_LoadMUS("music/game1.mp3");
    player.setAnimation(gRenderer);
    background.LoadImg("img/background1.png", gRenderer);
    background.rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    map.loadMap(gRenderer);
    rock.loadRock(gRenderer);
}

void free()
{
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    Mix_FreeMusic(gMusic);

    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}