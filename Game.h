#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include <fstream>
#include <vector>
using namespace std;

enum
{
    IDLE,
    JUMP,
    DEAD,
    TOTAL_ANIMATION
};
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

#define PLAYER_W 60
#define PLAYER_H 60
#define GRAVITY 2
#define MENU_PLAY_H 70
#define MENU_PLAY_W 270
