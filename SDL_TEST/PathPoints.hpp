
#ifndef PathPoints_hpp
#define PathPoints_hpp

#include "Utils.hpp"

using namespace Utils;

namespace PathPoints
{
    std::vector<LDPoint> makeSinglePath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints);
    std::vector<LDPoint> makeBiDirectionalPath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints);

    std::vector<LDPoint> clipFrom(std::vector<LDPoint>& sourcePath, LDPoint clipStart, int pixelDistanceBetweenPoints);
    std::vector<LDPoint> clipTo(std::vector<LDPoint>& sourcePath, LDPoint clipEnd, int pixelDistanceBetweenPoints);
    std::vector<LDPoint> clipBoth(std::vector<LDPoint>& sourcePath, LDPoint clipStart, LDPoint clipEnd, int pixelDistanceBetweenPoints);
    
    
    struct Path
    {
        Path(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistancebetweenPts, bool single);
        
        std::vector<LDPoint> path;
        int pixelDistanceBetweenPoints;
        
        size_t size();
        
        std::vector<LDPoint> dispatchClippedFrom(LDPoint clipStart);
        std::vector<LDPoint> dispatchClippedTo(LDPoint clipEnd);
        std::vector<LDPoint> dispatchClippedBoth(LDPoint clipStart, LDPoint clipEnd);
        
        operator std::vector<LDPoint>&();
        LDPoint& operator[](int index);
        void operator=(const std::vector<LDPoint>& newPath);
    };

};
    
#endif
