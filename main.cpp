#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Rock.h"
#include "Map.h"
#include "Menu.h"

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
Mix_Music *gMusic = NULL;
Mix_Music *score_sound = NULL;
Mix_Chunk *win = NULL;
Mix_Chunk *start = NULL;
TTF_Font *gFont = NULL;
SDL_Color color = {255, 153, 204};
Object score_text;
string SCORE;
SDL_Surface *icon;
SDL_Event event;
Object background;
Object back1;
Rock rock;
Map map;
Player player(map.platform);
Menu menu;
int score = 0;
int high_score;
bool QUIT = false;
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
    bool quitScore = false;
    loadMedia();
    SDL_SetWindowIcon(gWindow, icon);
    srand(time(0)); // set initial seed value to system clock
    while (!QUIT)
    {

        ifstream file("highscore.txt");
        file >> high_score;
        file.close();
        quit = false;
        quitScore = false;
        quitMenu = false;
        Mix_PlayChannel(-1, start, 0);
        while (!quitMenu)
        {
            // if (Mix_PlayingMusic() == 0)
            // {
            //     // Play the music
            //     Mix_PlayMusic(gMusic, -1);
            // }
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderClear(gRenderer);

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quitMenu = true;
                    quit = true;
                    quitScore = true;
                    QUIT = true;
                }
                menu.check_mouse(event, quitMenu);
            }
            background.Render(gRenderer);
            back1.Render(gRenderer);
            menu.draw(gRenderer);
            SDL_RenderPresent(gRenderer);
        }

        if (score >= 0 || quit == true)
        {
            player.reset();
            SDL_RenderClear(gRenderer);
            quit = false;
        }
        while (!quit)
        {
            // if (Mix_PlayingMusic() == 0)
            // {
            //     // Play the music
            //     Mix_PlayMusic(gMusic, -1);
            // }
            // If there is no music playing
            score_text.rect.y = 50;
            score_text.rect.x = SCREEN_WIDTH - score_text.rect.w;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quitMenu = true;
                    quit = true;
                    quitScore = true;
                }
                player.handleEvent(event);
            }
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderClear(gRenderer);

            player.update(map.platform, rock.rock, score);
            score_text.loadText(SCORE, color, gFont, gRenderer);
            rock.update(player.rect);
            background.Render(gRenderer);
            map.draw(gRenderer);
            player.draw(gRenderer, quit);
            rock.draw(gRenderer);
            SCORE = "SCORE:" + to_string(score);
            score_text.Render(gRenderer);
            SDL_Delay(30);
            if (score > high_score)
            {
                ofstream out("highscore.txt");
                out.clear();
                out << score;
            }
            SDL_RenderPresent(gRenderer);
        }

        QUIT = true;
        Mix_PlayChannel(-1, win, 0);
        while (!quitScore)
        {

            SDL_RenderClear(gRenderer);
            score_text.loadText(SCORE, color, gFont, gRenderer);
            score_text.rect.x = SCREEN_WIDTH / 2 - score_text.rect.w / 2;
            score_text.rect.y = SCREEN_HEIGHT / 2 - score_text.rect.h / 2;
            background.Render(gRenderer);
            SCORE = "YOUR SCORE IS : " + to_string(score);
            score_text.Render(gRenderer);
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quitMenu = true;
                    quit = true;
                    quitScore = true;
                }
                menu.Exit(event, quitScore, QUIT);
            }

            menu.drawExit(gRenderer);
            SDL_Delay(30);
            SDL_RenderPresent(gRenderer);
        }
        if (QUIT == false)
        {
            quitMenu = false;
            quit = false;
            quitScore = false;
        }
        if (score > high_score)
        {
            ofstream out("highscore.txt");
            out.clear();
            out << score;
        }
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
        gWindow = SDL_CreateWindow("PINK JUMP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
    start = Mix_LoadWAV("music/start.mp3");
    win = Mix_LoadWAV("music/win.mp3");
    menu.load(gRenderer);
    icon = IMG_Load("img/icon1.png");
    gMusic = Mix_LoadMUS("music/game1.mp3");
    score_sound = Mix_LoadMUS("music/score.wav");
    player.setAnimation(gRenderer);
    background.LoadImg("img/background1.png", gRenderer);
    back1.LoadImg("img/back1.png", gRenderer);
    back1.rect.h = 150;
    back1.rect.w = 400;
    back1.rect.x = SCREEN_WIDTH / 2 - back1.rect.w / 2;
    back1.rect.y = 100;
    gFont = TTF_OpenFont("font/game.ttf", 28);
    SCORE = "SCORE:" + to_string(0);
    score_text.loadText(SCORE, color, gFont, gRenderer);
    score_text.rect.x = SCREEN_WIDTH - score_text.rect.w;
    score_text.rect.y = 50;
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