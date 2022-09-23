#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include <math.h>


class Entity
{
public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f& getPos();
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    void setCurrentFrame(SDL_Rect p_rect);
    void setX(float p_x);
    void setY(float p_y);
    void setPos(Vector2f p_pos);
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};