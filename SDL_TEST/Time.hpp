
#ifndef Time_hpp
#define Time_hpp

#include "sdl2.hpp"


struct Time
{
    Time();
    
    Uint64 timeStamp;
    
    void setWait(int msToWait);
    bool waitOver();
};


#endif /* Time_hpp */
