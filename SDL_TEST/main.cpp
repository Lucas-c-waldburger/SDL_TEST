
#include <iostream>
#include <string>
#include "Flags.hpp"
#include "sdl2.hpp"
#include "Ship.hpp"
#include "Asteroid.hpp"
#include "TempObjectLifetimeManager.hpp"
#include "ScoreBox.hpp"



// TODO
    
    // make another velocityTime object in ship to handle rotational velocity

    // SCORE
    // maybe add reference to it inside objectDestructionManager?
    // add 10's place display for score
        // function to seperate score into 10s and 1s place
    // increase asteroid speed with score increase

GameFlags flags;

int main(int argc, char* argv[])
{
    try
    {
        sdl2::App app;
        sdl2::Window window("main", SCREEN_WIDTH, SCREEN_HEIGHT);
        sdl2::Renderer renderer(window);

        Ship ship{ renderer, 38, LDPoint{ 200, 200 } };
        AsteroidGenerator asteroidGenerator(renderer);
        ObjectDestructionManager objectDestructionManager;
        ScoreDisplay::ScoreBoard scoreBoard(renderer);
        
        SDL_Event e;
        while (!flags.isSet(quit))
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    flags.setFlag(quit);
                }
            }
            
            objectDestructionManager.resolveAll(ship, asteroidGenerator);
            if (ship.markedDestroy)
            {
                flags.setFlag(quit);
            }

            else
            {
                scoreBoard.setTotalScore(asteroidGenerator.getNumDestroyed());
                
                const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
                ship.handleKeyStates(keyStates);
                
                renderer.clear();
                
                ship.draw();
                ship.bulletGenerator.drawAll();
                asteroidGenerator.drawAll();
                scoreBoard.draw();
                
                
                renderer.present();
            }
        }
    }

    catch (std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }


    return 0;
}
