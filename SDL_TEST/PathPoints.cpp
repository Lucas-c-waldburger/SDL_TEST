
#include "PathPoints.hpp"

std::vector<LDPoint> PathPoints::makeSinglePath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> singlePath;

    int i = startingDistanceFromV1;
    LDPoint projectedPoint = LinePoints::extendLine(v1, v2, i);

    while (LinePoints::pointWithinScreenBounds(projectedPoint)) // CONSOLIDATE & MOVE LINEPOINTS NAMESPACE FUNCS INTO SOMETHING BETTER
    {
        singlePath.push_back(projectedPoint);
        i += pixelDistanceBetweenPoints;
        projectedPoint = LinePoints::extendLine(v1, v2, i);
    }
    
    return singlePath;
}

std::vector<LDPoint> PathPoints::makeBiDirectionalPath(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> biDirectionalPath = makeSinglePath(v1, v2, 0, pixelDistanceBetweenPoints);
    std::vector<LDPoint> backwardPath = makeSinglePath(v2, v1, startingDistanceFromV1, pixelDistanceBetweenPoints);
    
    biDirectionalPath.insert(biDirectionalPath.end(), backwardPath.rbegin(), backwardPath.rend());
    
    return biDirectionalPath;
}



std::vector<LDPoint> PathPoints::clipFrom(std::vector<LDPoint>& sourcePath, LDPoint clipStart, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> clippedPath;

    auto closestPointToClipStart = [&clipStart, &pixelDistanceBetweenPoints](LDPoint& p)
    {
        return ((clipStart.x >= p.x - pixelDistanceBetweenPoints && clipStart.x <= p.x + pixelDistanceBetweenPoints) &&
                (clipStart.y >= p.y - pixelDistanceBetweenPoints && clipStart.y <= p.y + pixelDistanceBetweenPoints));
    };
    
    auto clipped = std::find_if(sourcePath.begin(), sourcePath.end(), closestPointToClipStart);
    
    return std::vector<LDPoint>(clipped, sourcePath.end());
}


std::vector<LDPoint> PathPoints::clipTo(std::vector<LDPoint>& sourcePath, LDPoint clipEnd, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> clippedPath;

    auto closestPointToClipEnd = [&clipEnd, &pixelDistanceBetweenPoints](LDPoint& p)
    {
        return ((clipEnd.x >= p.x - pixelDistanceBetweenPoints && clipEnd.x <= p.x + pixelDistanceBetweenPoints) &&
                (clipEnd.y >= p.y - pixelDistanceBetweenPoints && clipEnd.y <= p.y + pixelDistanceBetweenPoints));
    };
    
    auto clipped = std::find_if(sourcePath.begin(), sourcePath.end(), closestPointToClipEnd);
    
    return std::vector<LDPoint>(sourcePath.begin(), clipped);
}


std::vector<LDPoint> PathPoints::clipBoth(std::vector<LDPoint>& sourcePath, LDPoint clipStart, LDPoint clipEnd, int pixelDistanceBetweenPoints)
{
    std::vector<LDPoint> clippedPath;
    
    auto closestPointToClipStart = [&clipStart, &pixelDistanceBetweenPoints](LDPoint& p)
    {
        return ((clipStart.x >= p.x - pixelDistanceBetweenPoints && clipStart.x <= p.x + pixelDistanceBetweenPoints) &&
                (clipStart.y >= p.y - pixelDistanceBetweenPoints && clipStart.y <= p.y + pixelDistanceBetweenPoints));
    };

    auto closestPointToClipEnd = [&clipEnd, &pixelDistanceBetweenPoints](LDPoint& p)
    {
        return ((clipEnd.x >= p.x - pixelDistanceBetweenPoints && clipEnd.x <= p.x + pixelDistanceBetweenPoints) &&
                (clipEnd.y >= p.y - pixelDistanceBetweenPoints && clipEnd.y <= p.y + pixelDistanceBetweenPoints));
    };
    
    auto clippedStart = std::find_if(sourcePath.begin(), sourcePath.end(), closestPointToClipStart);
    auto clippedEnd = std::find_if(clippedStart, sourcePath.end(), closestPointToClipEnd);
    
    return std::vector<LDPoint>(clippedStart, clippedEnd);
}


PathPoints::Path::Path(LDPoint v1, LDPoint v2, int startingDistanceFromV1, int pixelDistancebetweenPts, bool single) : pixelDistanceBetweenPoints(pixelDistancebetweenPts)
{
    path = (single) ?
        PathPoints::makeSinglePath(v1, v2, startingDistanceFromV1, pixelDistancebetweenPts) :
        PathPoints::makeBiDirectionalPath(v1, v2, startingDistanceFromV1, pixelDistancebetweenPts);
}


size_t PathPoints::Path::size()
{
    return path.size();
}


std::vector<LDPoint> PathPoints::Path::dispatchClippedFrom(LDPoint clipStart)
{
    return PathPoints::clipFrom(path, clipStart, pixelDistanceBetweenPoints);
}

std::vector<LDPoint> PathPoints::Path::dispatchClippedTo(LDPoint clipEnd)
{
    return PathPoints::clipTo(path, clipEnd, pixelDistanceBetweenPoints);
}

std::vector<LDPoint> PathPoints::Path::dispatchClippedBoth(LDPoint clipStart, LDPoint clipEnd)
{
    return PathPoints::clipBoth(path, clipStart, clipEnd, pixelDistanceBetweenPoints);
}


PathPoints::Path::operator std::vector<LDPoint>&()
{
    return path;
}

LDPoint& PathPoints::Path::operator[](int index)
{
    if (index >= path.size())
        throw std::out_of_range("Index exceeds path size");
        
    return path[index];
}

void PathPoints::Path::operator=(const std::vector<LDPoint>& newPath)
{
    path.clear();
    this->path = newPath;
}
