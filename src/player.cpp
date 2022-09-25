#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include "player.h"
#include "entity.h"
#include "math.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex) 
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;
    this->setCurrentFrame(rect);
}

Vector2f Player::getVelocity()
{
    return velocity;
}

Vector2f Player::getInitialMousePos()
{
    return initialMousePos;
}

Vector2f Player::getLaunch(Vector2f a, Vector2f b)
{   
    float x = (b.x - a.x) * -1;
    float y = (b.y - a.y) * -1;
    return Vector2f(x, y);
}


void Player::setVelocity(Vector2f p_vel)
{
    velocity = p_vel;
}

void Player::setInitialMousePos(Vector2f p_pos)
{
    initialMousePos = p_pos;
}

bool Player::checkColided(Entity& p_target)
{
    if (this->getPos().x + this->getCurrentFrame().w >= p_target.getPos().x &&    
        this->getPos().x <= p_target.getPos().x + p_target.getCurrentFrame().w && 
        this->getPos().y + this->getCurrentFrame().h >= p_target.getPos().y &&    
        this->getPos().y <= p_target.getPos().y + p_target.getCurrentFrame().h)
    { 
        return true;
    }
    return false;
}

void Player::update(double deltaTime, bool mouseDown, bool mousePressed)
{   
    int mouseX, mouseY;
    if(mouseDown)
    {
        if(mousePressed)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePos(Vector2f(mouseX, mouseY));
        }
        SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity(getLaunch(initialMousePos, Vector2f(mouseX, mouseY)));

        velocity = velocity / 300;
        velocity.x *= deltaTime;
        velocity.y *= deltaTime;
    }
    else
    {
        if(getPos().y < 339 - velocity.y)
        {
            grounded = false;
        }
        else{
            grounded = true;
        }

        if(getPos().x + velocity.x <= 0 || getPos().x + velocity.x >= 184 )
        {
            velocity.x *= -1;
        }

        if(!grounded)
        {
            velocity.y = velocity.y + GRAVITY * deltaTime;
        }
        else{
            velocity.y *= -0.5;
            velocity.x *= 0.3;
        }

        setPos(getPos() + velocity);
        velocity.print();
    }
}