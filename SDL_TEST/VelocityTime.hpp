
#ifndef VelocityTime_hpp
#define VelocityTime_hpp

#include "Time.hpp"
#include <iostream>

const int MAX_DELAY = 300, MIN_DELAY = 10, BASE_DELAY_CHANGE_AMOUNT = 1;

struct VelocityTime : public Time
{
    VelocityTime(int maxDel, int minDel, int baseDelChangeAmnt);
    
    int maxDelay, minDelay;
    int currentDelay;
    int baseDelayChangeAmount;
    
    void updateCurrentDelay(bool moveKeyDown);
    bool decideMovement(bool moveKeyDown);
};



#endif
