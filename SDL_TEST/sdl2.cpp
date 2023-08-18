#include "sdl2.hpp"


// APP
sdl2::App::App()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

sdl2::App::~App()
{
    SDL_Quit();
}


// WINDOW
sdl2::Window::Window(const char* title, int w, int h, int x, int y, Uint32 flags)
{
    pWindow = SDL_CreateWindow(title, x, y, w, h, flags);

    if (!pWindow)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

sdl2::Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

sdl2::Window::operator SDL_Window* ()
{
    return pWindow;
}


// RENDERER
sdl2::Renderer::Renderer(SDL_Window* win)
{
    pRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!pRenderer)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

sdl2::Renderer::~Renderer()
{
    SDL_DestroyRenderer(pRenderer);
}

void sdl2::Renderer::clear()
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(pRenderer);
}

void sdl2::Renderer::present()
{
    SDL_RenderPresent(pRenderer);
}

sdl2::Renderer::operator SDL_Renderer* ()
{
    return pRenderer;
}


