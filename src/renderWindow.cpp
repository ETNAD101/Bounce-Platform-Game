#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include "renderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) 
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
}

void RenderWindow::background(SDL_Texture* p_img)
{
    SDL_RenderCopy(renderer, p_img, NULL, NULL);
}

void RenderWindow::render(Entity& p_e)
{
    SDL_Rect src;
	src.x = p_e.getCurrentFrame().x;
	src.y = p_e.getCurrentFrame().y;
	src.w = p_e.getCurrentFrame().w;
	src.h = p_e.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_e.getPos().x * 2;
	dst.y = p_e.getPos().y * 2;
	dst.w = p_e.getCurrentFrame().w * 2;
	dst.h = p_e.getCurrentFrame().h * 2;

    SDL_RenderCopy(renderer, p_e.getTex(), &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}