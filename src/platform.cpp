#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "entity.h"
#include "platform.h"
#include "math.h"

Platform::Platform(Vector2f p_pos, SDL_Texture* p_tex, Vector2f size)
    :Entity(p_pos, p_tex)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = size.x;
    rect.h = size.y;
    this->setCurrentFrame(rect);
}