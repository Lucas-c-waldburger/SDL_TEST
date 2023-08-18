

#include "VelocityTime.hpp"

VelocityTime::VelocityTime(int maxDel, int minDel, int baseDelChangeAmnt) : maxDelay(maxDel), minDelay(minDel), baseDelayChangeAmount(baseDelChangeAmnt), currentDelay(maxDelay)
{}

void VelocityTime::updateCurrentDelay(bool moveKeyDown)
{
    int currentDelayChangeAmount = (currentDelay / 10) + (currentDelay / 15);
    
    currentDelay += (moveKeyDown) ? -currentDelayChangeAmount : currentDelayChangeAmount;
    
    if (currentDelay < minDelay)
    {
        currentDelay = minDelay;
    }
    else if (currentDelay > maxDelay)
    {
        currentDelay = maxDelay;
    }
}

bool VelocityTime::decideMovement(bool moveKeyDown)
{
    if (waitOver())
    {
        updateCurrentDelay(moveKeyDown);
        setWait(currentDelay);
//        std::cout << "WAIT TIME: " << currentDelay << '\n';
        return true;
    }
    
    return false;
}

