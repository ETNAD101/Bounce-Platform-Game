#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include <vector>
#include "player.h"
#include "entity.h"
#include "platform.h"
#include "math.h"
#include "def.h"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex) 
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;
    canMove = true;
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

/**Calculates velocity based on how far the mouse was dragged**/
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

/**Checks collisions for each side individualy*/
int Player::checkCollided(Entity& p_target)
{
    // Top
    if((getPos().y + velocity.y < p_target.getPos().y + p_target.getCurrentFrame().h && 
       getPos().x + velocity.x < p_target.getPos().x + p_target.getCurrentFrame().w &&
       getPos().x + getCurrentFrame().w + velocity.x > p_target.getPos().x &&
       getPos().y + getCurrentFrame().h + velocity.y > p_target.getPos().y + p_target.getCurrentFrame().h) ||
       getPos().y + velocity.y < 0
       ) {
        std::cout << "Top Hit\n";
        return TOP;
    }

    // Bottom
    if((getPos().y + velocity.y < p_target.getPos().y && 
       getPos().x + velocity.x < p_target.getPos().x + p_target.getCurrentFrame().w &&
       getPos().x + getCurrentFrame().w + velocity.x > p_target.getPos().x && 
       getPos().y + getCurrentFrame().h + velocity.y > p_target.getPos().y) ||
       getPos().y + velocity.y >= 339
       ) {
        std::cout << "Bottom Hit\n";
        grounded = true;
        return BOTTOM;
    }

    // Left
    if((getPos().x + velocity.x < p_target.getPos().x + p_target.getCurrentFrame().w &&
       getPos().y + velocity.y < p_target.getPos().y + p_target.getCurrentFrame().h &&
       getPos().y + getCurrentFrame().h + velocity.y > p_target.getPos().y &&
       getPos().x + getCurrentFrame().w + velocity.x > p_target.getPos().x + p_target.getCurrentFrame().x) ||
       getPos().x + velocity.x < 0
       ) {
        std::cout << "Left hit\n";
        return LEFT;
    }

    // Right
    if((getPos().x + p_target.getCurrentFrame().w + velocity.x > p_target.getPos().x &&
       getPos().x + velocity.x < p_target.getPos().x &&
       getPos().y + velocity.y < p_target.getPos().y + p_target.getCurrentFrame().h &&
       getPos().y + getCurrentFrame().h + velocity.y > p_target.getPos().y) ||
       getPos().x + velocity.x >= 184  
       ) {
        std::cout << "Right hit\n";
        return RIGHT;
       }

    return 0;
}

/**changes velocity depending on what collieded**/
void Player::bounce(int dir) {
    if(dir == 1) {
        velocity.y *= -1;
    }
    if(dir == 2) {
        velocity.y *= -0.7;
        velocity.x *= 0.3;
    }
    if(dir > 2) {
        velocity.x *= -0.9;
    }
}

/**Main player update loop**/
void Player::update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Platform>& platforms)
{   
    int mouseX, mouseY;
    int collisionDir;
    if(mouseDown)
    {
        /**Measure player launch velocity**/
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
        /**Check if player collided with any platform**/
        for(Platform p : platforms)
        {
            collisionDir = checkCollided(p);
            bounce(collisionDir);
        }

        /**Checks if player is on the ground**/
        if(collisionDir != 2) {
            grounded = false;
        } 

        /**Gravity and friction**/
        if(!grounded)
        {
            velocity.y = velocity.y + GRAVITY * deltaTime;
        }
        
        /**Update position every frame**/
        velocity.print();
        setPos(getPos() + velocity);

        if(abs(velocity.y) < 0.05) {
            velocity.y = 0;
        }

        if(abs(velocity.x) < 0.05) {
            velocity.x = 0;
        }
    }  
}