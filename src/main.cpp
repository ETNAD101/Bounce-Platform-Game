#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <cmath>
#include "renderWindow.h"
#include "math.h"
#include "entity.h"
#include "player.h"
#include "platform.h"
#include "settings.h"

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

RenderWindow window(TITLE, WIDTH, HEIGHT);

Player player(Vector2f(WIDTH/4 - 8, HEIGHT/4 - 16), window.loadTexture(PLAYER_PATH));

std::vector<Platform> platforms = 
{
    Platform(Vector2f(0, 0), window.loadTexture(DEBUG_PATH), Vector2f(32, 16)),
    Platform(Vector2f(50, 50), window.loadTexture(DEBUG_PATH), Vector2f(16, 16)),
    Platform(Vector2f(30, 150), window.loadTexture(DEBUG_PATH), Vector2f(32, 16)),

};

SDL_Event event;

bool running = true;
bool mouseDown;
bool mousePressed;
bool reset;

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL_Init has failed, ERROR: " << SDL_GetError() << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_init has failed, ERROR: " << SDL_GetError() << std::endl;
    }
}

void events()
{
    /**Event loop**/
    while(SDL_PollEvent(&event))
    {   
        /**Events**/
        SDL_PumpEvents();  // make sure we have the latest mouse state.

        mousePressed = false;

        switch(event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
                mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
        case SDL_KEYDOWN:
            player.setPos(Vector2f(100, 0));
            player.setVelocity(Vector2f(0, 0));
        }
        
    }
}

void update()
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());

    player.update(deltaTime, mouseDown, mousePressed, platforms);

}

void graphics()
{
    /**Clearing**/
    window.clear();

    /**Rendering**/
    for(Platform p : platforms)
    {
        window.render(p);
    }
    window.render(player);
    window.display();
}

int main(int argc, char* argv[])
{   
    while(running)
    {
        events();
        update();
        graphics();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}