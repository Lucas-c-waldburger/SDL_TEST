
#include "Time.hpp"

Time::Time() : timeStamp(SDL_GetTicks64())
{}


void Time::setWait(int msToWait)
{
    timeStamp = SDL_GetTicks64() + msToWait;
}

bool Time::waitOver()
{
    return SDL_GetTicks64() >= timeStamp;
}
