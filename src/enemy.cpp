#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <cmath>
#include <vector>
#include "entity.h"
#include "platform.h"
#include "math.h"
#include "def.h"
#include "enemy.h"

Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex, float p_pos1, float p_pos2) 
    :Entity(p_pos, p_tex)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 16;
    rect.h = 16;
    moveLeft = true;
    this->setCurrentFrame(rect);
    pos1 = p_pos1;
    pos2 = p_pos2;
}

Vector2f Enemy::getVelocity() {
    return velocity;
}

int Enemy::checkCollided(Entity& p_target) {

}

void Enemy::update(double deltaTime, bool mouseDown, bool mousePressed) {
    if(moveLeft) {
        this->setX(this->getPos().x - (0.05 * deltaTime));
    }else {
        this->setX(this->getPos().x + (0.05 * deltaTime));
    }

    if(this->getPos().x + this->getCurrentFrame().w >= pos2) {
        moveLeft = true;
    }
    if(this->getPos().x <= pos1) {
        moveLeft = false;
    }

    std::cout << moveLeft << std::endl;
    this->getPos().print();
}