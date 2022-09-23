#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include "entity.h"
#include "math.h"

class Player : public Entity
{
public:
    Player(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f getVelocity();
    Vector2f getInitialMousePos();
    Vector2f getLaunch(Vector2f a, Vector2f b);
    void setVelocity(Vector2f p_vel);
    void setInitialMousePos(Vector2f p_pos);
    bool checkColided(Entity& p_target);
    void update(double deltaTime, bool mouseDown, bool mousePressed);
private:
    const float GRAVITY = 0.03;
    const float FRICTION = 0.03;
    Vector2f velocity;
    Vector2f initialMousePos;
    bool canMove;
    bool grounded;
};