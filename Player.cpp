#include "Player.h"

Player::Player(Object platform[7])
{
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    int x = rand() % 6 + 0;
    rect = {SCREEN_WIDTH / 2, 0, PLAYER_W, PLAYER_H};
    onGround = false;
    speed = false;
    idle = true;
    isRight = true;
    isLeft = false;
    isJump = false;
    isAttack = false;
    idle_right = true;
    check = false;
    dead = false;
    heart = 3;
}

Player::~Player()
{
    Free();
}

void Player::attack()
{
    isAttack = true;
    isLeft = false;
    isRight = false;
    idle = false;
}

void Player::jump()
{

    if (!isJump)
    {
        isJump = true;
        vy = -27;
    }
}
void Player::moveLeft()
{
    vx = -20;
    idle = false;
    isLeft = true;
    idle_right = false;
    isRight = false;
}
void Player::moveRight()
{
    isRight = true;
    idle = false;
    vx = 20;
    idle_right = true;
    isLeft = false;
}
void Player::stop()
{
    vx = 0;
    idle = true;
}

void Player::SpeedTele()
{
    if (!speed)
    {
        if (vx > 0 || idle_right)
            rect.x += 100;
        if (vx < 0 || !idle_right)
            rect.x -= 100;
        if (vy < 0)
            rect.y -= 100;

        speed = true;
    }
}

void Player::draw(SDL_Renderer *gRenderer, bool &quit)
{
    // draw heart of player
    if (heart >= 0)
    {
        for (int i = 0; i < heart; i++)
        {
            hearts[i].Render(gRenderer, NULL);
        }
    }
    if (dead)
    {
        int frame = cnt / 8;
        Animation[DEAD].rect.x = rect.x;
        Animation[DEAD].rect.y = rect.y;
        Animation[DEAD].Render(gRenderer, &dead_rect[frame]);
        cnt++;
        if (frame >= 8)
        {
            quit = true;
        }
    }

    else if (idle == true && isJump != true)
    {
        int frame = cnt / 15;
        Animation[IDLE].rect.x = rect.x;
        Animation[IDLE].rect.y = rect.y;
        if (idle_right)
        {
            Animation[IDLE].Render(gRenderer, &idle_rect[frame]);
        }
        else
        {
            Animation[IDLE].RenderEx(gRenderer, &idle_rect[frame]);
        }
        cnt++;
        if (frame >= 4)
            cnt = 0;
    }
    else if (isRight && !dead)
    {
        int frame = cnt / 10;
        Animation[JUMP].rect.x = rect.x;
        Animation[JUMP].rect.y = rect.y;
        Animation[JUMP].Render(gRenderer, &jump_rect[frame]);
        cnt++;
        if (frame >= 8)
            cnt = 0;
    }
    else if (isLeft && !dead)
    {
        int frame = cnt / 8;
        Animation[JUMP].rect.x = rect.x;
        Animation[JUMP].rect.y = rect.y;
        Animation[JUMP].RenderEx(gRenderer, &jump_rect[frame]);
        cnt++;
        if (frame >= 8)
            cnt = 0;
    }
}

void Player::handleEvent(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            jump();
            break;
        case SDLK_LEFT:
            moveLeft();
            break;
        case SDLK_RIGHT:
            moveRight();
            break;
        case SDLK_x:
            SpeedTele();
            break;
        case SDLK_j:
            // attack();
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            stop();
            break;
        case SDLK_RIGHT:
            stop();
            break;
        case SDLK_x:
            if (!speed)
            {
                if (vx > 0)
                    vx -= 1;
                else if (vx < 0)
                    vx += 1;
                if (vy > 0)
                    vy -= 10;
                else if (vy < 0)
                    vy += 10;
            }
            break;
        case SDLK_j:

        default:
            break;
        }
    }
}
void Player::update(Object platform[7], Object rock[2])
{
    // Apply gravity
    if (!onGround && !dead)
        vy += GRAVITY;

    // Move the player horizontally

    // is deaded

    if (dead)
    {
        vx = 0;
        vy = 0;
    }

    if (vx > 50)
    {
        vx = 50;
    }
    if (vx <= -50)
    {
        vx = -50;
    }
    rect.x += vx;

    // Move the player vertically
    if (rect.x < 0)
    {
        rect.x = SCREEN_WIDTH - PLAYER_W;
    }

    if (rect.x + PLAYER_W > SCREEN_WIDTH)
    {
        rect.x = 0;
    }

    if (vy > 50)
    {
        vy = 50;
    }
    if (vy <= -50)
    {
        vy = -50;
    }
    rect.y += vy;
    // Check for collisions with the ground
    for (int i = 0; i < 7; i++)
    {
        // va cham
        if (rect.y + PLAYER_H >= platform[i].rect.y + 10 &&
            rect.y <= platform[i].rect.y - 20 + platform[i].rect.h &&
            rect.x + PLAYER_W >= platform[i].rect.x + 15 &&
            rect.x <= platform[i].rect.x + platform[i].rect.w - 15 &&
            vy >= 0 && !dead)
        {

            rect.y = platform[i].rect.y - PLAYER_H;

            isJump = false;

            vy = 0;
            onGround = true;
            speed = false;
        }
    }

    // check collision with rock
    for (int i = 0; i < 2; i++)
    {
        if (checkCollision(rock[i].rect, rect) && !dead)
        {
            heart--;
            if (heart < 0)
                dead = true;
            if (heart >= 0)
            {
                rock[i].rect.y = 0;
                rock[i].rect.x = rect.x + rand() % 500 + 0;

                rect.y = 0;
                int k = rand() % 7 + 0;
                rect.x = platform[k].rect.x;
                rect.y = platform[k].rect.y - platform[k].rect.h - PLAYER_H;
            }
        }
    }

    if (rect.y <= 0)
    {
        rect.y = 0;
        vy = 0;
    }

    if (rect.y + PLAYER_H >= SCREEN_HEIGHT && !dead)
    {
        heart--;
        if (heart >= 0)
        {
            int k = rand() % 7 + 0;
            rect.x = platform[k].rect.x;
            rect.y = platform[k].rect.y - platform[k].rect.h - PLAYER_H;

            onGround = true;
            speed = false;
            isJump = false;
        }
    }

    else
    {
        onGround = false;
    }

    if (heart < 0)
        dead = true;
}
void Player::setAnimation(SDL_Renderer *gRenderer)
{

    Animation[IDLE].LoadImg("img/Idle.png", gRenderer);
    Animation[IDLE].rect = {0, 0, PLAYER_W, PLAYER_H};
    for (int i = 0; i < 4; i++)
    {
        idle_rect[i] = {i * 32,
                        0,
                        32,
                        32};
    }

    Animation[JUMP].LoadImg("img/Jump.png", gRenderer);
    Animation[JUMP].rect = {0, 0, PLAYER_W, PLAYER_H};
    for (int i = 0; i < 8; i++)
    {
        jump_rect[i] = {i * 32, 0, 32, 32};
    }

    Animation[DEAD].LoadImg("img/dead.png", gRenderer);
    Animation[DEAD].rect = {0, 0, PLAYER_W, PLAYER_W};
    for (int i = 0; i < 8; i++)
    {
        dead_rect[i] = {i * 32, 0, 32, 32};
    }

    for (int i = 0; i < heart; i++)
    {
        hearts[i].LoadImg("img/heart.png", gRenderer);
        hearts[i].rect = {SCREEN_WIDTH - 35 * (i + 1), 0, 40, 40};
    }
}
