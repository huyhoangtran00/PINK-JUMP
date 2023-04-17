#include "Game.h"
#include "Object.h"

class Player : public Object
{
private:
    int x, y;
    int vx, vy;
    bool onGround;
    bool speed;
    bool idle;
    bool isRight;
    bool isLeft;
    bool isJump;
    bool isAttack;
    int cnt = 0;
    bool check;
    bool dead;
    bool idle_right;
    Mix_Chunk *jump_sound;
    Mix_Chunk *dead_sound;
    Mix_Chunk *revive_sound;
    Mix_Chunk *speed_sound;
    Object Animation[TOTAL_ANIMATION];
    Object CurrentAnimation;
    Object hearts[3];
    int heart;
    SDL_Rect dead_rect[8];
    SDL_Rect jump_rect[8];
    SDL_Rect idle_rect[4];
    bool check_score[7];
    int score = 0;
    SDL_Point bf;

public:
    Player()
    {
        ;
    }
    Player(Object platform[7]);
    ~Player();
    void handleEvent(SDL_Event event);
    void jump();
    void moveLeft();
    void moveRight();
    void stop();
    void attack();
    void SpeedTele();
    void draw(SDL_Renderer *gRenderer, bool &quit);
    void update(Object plasform[7], Object rock[2], int &score);
    void setAnimation(SDL_Renderer *gRenderer);
    void load_sound();
    void reset();
};
