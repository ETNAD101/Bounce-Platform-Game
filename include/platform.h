#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "entity.h"
#include "math.h"

class Platform : public Entity
{
public:
    Platform(Vector2f p_pos, SDL_Texture* p_tex, Vector2f size);
    void update(double& p_deltaTime);
};