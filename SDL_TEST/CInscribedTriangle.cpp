
#include "CInscribedTriangle.hpp"


CInscribedTriangle::CInscribedTriangle(SDL_Renderer* renderer, int r, LDPoint c) : CircleDraw(renderer, r, c), facingNewDirection(false), currentForwardPathIndex(1), bulletGenerator(BulletGenerator{ rendererCpy })
{
    sortPerimeterPoints();
    recenter();

    trianglePointIndexes.reserve(3);
    assignTrianglePointIndexes();
    updateTranglePoints();

    generateForwardPathPoints();

}

void CInscribedTriangle::draw()
{
    SDL_SetRenderDrawColor(rendererCpy, 0, 0, 0 , 0xFF);
    updateTranglePoints();
    SDL_RenderDrawLines(rendererCpy, trianglePoints, 4);
    SDL_RenderDrawPoints(rendererCpy, &forwardPathPoints[0], forwardPathPoints.size());
}


void CInscribedTriangle::rotate(int amount)
{
    int ppSize = perimeterPoints.size() - 1;
    int projected = 0;

    for (int& tpi : trianglePointIndexes)
    {
        projected = (tpi + amount) % ppSize;
        
        if (projected < 0)
            projected += ppSize;

        tpi = projected;
    }

    facingNewDirection = true;
    generateForwardPathPoints();
}


void CInscribedTriangle::goForward()
{
    //if (facingNewDirection)
    //{
    //    generateForwardPathPoints();
    //    facingNewDirection = false;
    //}

    LDPoint head = perimeterPoints[trianglePointIndexes[0]];

    //std::cout << "HEAD: " << head << "\nFORWARD PATH POINTS:\n";
    //for (auto& p : forwardPathPoints)
    //    std::cout << '\t' << p << '\n';
    //if (head == forwardPathPoints.back())
    //    return;

    LDPoint nextPoint = forwardPathPoints[currentForwardPathIndex];

    if (pointWithinBounds(head))
    {
        move(nextPoint - center);
        ++currentForwardPathIndex;
    }
}

void CInscribedTriangle::shoot()
{
}


void CInscribedTriangle::sortPerimeterPoints()
{
    std::vector<LDPoint> temp;
    temp.reserve(perimeterPoints.size());

    std::copy_if(perimeterPoints.begin(), perimeterPoints.end(), std::back_inserter(temp), [](LDPoint& p)
        {
            return p.x <= 0;
        });

    std::stable_sort(temp.begin(), temp.end(), [](const LDPoint& p1, const LDPoint& p2)
        {
            return p1.x < p2.x;
        });

    auto posYs1 = std::stable_partition(temp.begin(), temp.end(), [](LDPoint& p)
        {
            return p.y <= 0;
        });

    std::reverse(temp.begin(), posYs1);

    perimeterPoints = temp;

    std::transform(++temp.begin(), --temp.end(), std::back_inserter(perimeterPoints), [](LDPoint& p)
        {
            p.x = -p.x; p.y = -p.y;
            return p;
        });
}

void CInscribedTriangle::assignTrianglePointIndexes()
{
    int size = perimeterPoints.size();
    trianglePointIndexes = { size - 1, static_cast<int>(size * 0.33), static_cast<int>(size * 0.66) };
}


void CInscribedTriangle::generateForwardPathPoints()
{
    forwardPathPoints.clear();

    int i = 0;
    LDPoint head = perimeterPoints[trianglePointIndexes[0]];
    LDPoint projectedPoint = extendLinePoint(center, head, i);

    while (pointWithinBounds(projectedPoint))
    {
        forwardPathPoints.push_back(projectedPoint);
        i += PIXELS_MOVE_PER_FRAME;
        projectedPoint = extendLinePoint(center, head, i);
    }

    currentForwardPathIndex = 1;
}

LDPoint CInscribedTriangle::extendLinePoint(LDPoint& A, LDPoint& B, int distance)
{
    LDPoint C;

    double lenAB = sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));

    C.x = A.x + (distance * (B.x - A.x) / lenAB);
    C.y = A.y + (distance * (B.y - A.y) / lenAB);

    return C;
}

std::vector<LDPoint> CInscribedTriangle::clipForwardPathFromHead() // returns copy of forward path points from the first point that is at/past the head of triangle
{
    LDPoint head = perimeterPoints[trianglePointIndexes[0]];
    
    auto closestPointToHead = [&head](LDPoint& p)
    {
        return ((head.x >= p.x - 2 && head.x <= p.x + 2) && (head.y >= p.y - 2 && head.y <= p.y + 2));
    };
    
    auto clippedPath = std::find_if(forwardPathPoints.begin(), forwardPathPoints.end(), closestPointToHead);
    
    return std::vector<LDPoint>(clippedPath, forwardPathPoints.end());
}
    
bool CInscribedTriangle::pointWithinBounds(LDPoint& p)
{
    return ((p.x > 0 && p.x < SCREEN_WIDTH) &&
        (p.y > 0 && p.y < SCREEN_HEIGHT));
}


void CInscribedTriangle::handleKeyStates(const Uint8*& keystates)
{
    if (keystates[SDL_SCANCODE_A])
        rotate(2);

    else if (keystates[SDL_SCANCODE_D])
        rotate(-2);

    if (keystates[SDL_SCANCODE_W])
        goForward();

    if (keystates[SDL_SCANCODE_SPACE])
    {
        if (bulletGenerator.time.waitOver())
            bulletGenerator.makeBullet(clipForwardPathFromHead());
    }
}

void CInscribedTriangle::updateTranglePoints()
{
    trianglePoints[0] = perimeterPoints[trianglePointIndexes[0]];
    trianglePoints[1] = perimeterPoints[trianglePointIndexes[1]];
    trianglePoints[2] = perimeterPoints[trianglePointIndexes[2]];
    trianglePoints[3] = perimeterPoints[trianglePointIndexes[0]];
}
