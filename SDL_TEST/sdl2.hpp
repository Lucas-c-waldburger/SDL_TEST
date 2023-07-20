
#ifndef sdl2_hpp
#define sdl2_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdexcept>


namespace sdl2
{
    class App
    {
    public:
        App();
        ~App();
    };

    class Window
    {
    public:
        Window(const char* title, int w, int h, int x = SDL_WINDOWPOS_UNDEFINED,
            int y = SDL_WINDOWPOS_UNDEFINED, Uint32 flags = SDL_WINDOW_SHOWN);
        ~Window();

        operator SDL_Window* ();

    private:
        SDL_Window* pWindow;
    };

    class Renderer
    {
    public:
        Renderer(SDL_Window* win);
        ~Renderer();

        void clear();
        void present();

        operator SDL_Renderer* ();

    private:
        SDL_Renderer* pRenderer;

    };
















}


#endif /* sdl2_hpp */
