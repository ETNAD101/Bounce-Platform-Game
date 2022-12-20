#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include <vector>
#include "entity.h"
#include "platform.h"
#include "math.h"
#include "def.h"

class Enemy : public Entity
{
public:
    Enemy(Vector2f p_pos, SDL_Texture* p_tex, float pos1, float pos2);
    Vector2f getVelocity();
    int checkCollided(Entity& p_target);
    void update(double deltaTime, bool mouseDown, bool mousePressed);
private:
    const float FRICTION = 0.03;
    Vector2f velocity;
    float pos1;
    float pos2;
    bool moveLeft;
};