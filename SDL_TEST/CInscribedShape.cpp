
#include "CInscribedShape.hpp"
#include <sstream>

CInscribedShape::CInscribedShape(SDL_Renderer* renderer, int r, LDPoint c, int numVerts) : CircleDraw(renderer, r, c), numVertices(numVerts)
{
    init();
}

CInscribedShape::~CInscribedShape()
{
    rendererCpy = nullptr;
}

const std::vector<int>& CInscribedShape::getVertexIndecies()
{
    return vertexIndecies;
}

const std::vector<LDPoint>& CInscribedShape::getVertexPoints()
{
    return vertexPoints;
}

void CInscribedShape::init()
{
    if (numVertices > perimeterPoints.size())
    {
        std::stringstream exWhat("Number of shape vertices cannot exceed number of perimeter points in base circle shape.\n");
        exWhat << "Current available points for radius size " << std::to_string(radius) << ": " << std::to_string(perimeterPoints.size());
        
        throw std::out_of_range(exWhat.str());
    }
    
    nonSequentialPerimeterPoints = perimeterPoints;
    sortPerimeterPoints();
    recenter();

    vertexPoints.reserve(numVertices + 1);
    assignVertexIndexes();
    updateVertexPoints();
}

void CInscribedShape::move(LDPoint newP)
{
    CircleDraw::move(newP);
    
    std::for_each(nonSequentialPerimeterPoints.begin(), nonSequentialPerimeterPoints.end(), [&newP](LDPoint& p) { p += newP; });
}

void CInscribedShape::recenter()
{
    CircleDraw::recenter();
    
    std::for_each(nonSequentialPerimeterPoints.begin(), nonSequentialPerimeterPoints.end(), [&](LDPoint& p) { p += center; });
}


void CInscribedShape::draw()
{
    SDL_SetRenderDrawColor(rendererCpy, 0xFF, 0xFF, 0xFF, 0xFF);
    updateVertexPoints(); // MOVE TO ROTATE?
    SDL_RenderDrawLines(rendererCpy, &vertexPoints[0], vertexPoints.size());
}

void CInscribedShape::rotate(int amount)
{
    int ppSize = perimeterPoints.size() - 1;
    int projected = 0;

    for (int& vi : vertexIndecies)
    {
        projected = (vi + amount) % ppSize;
        
        if (projected < 0)
            projected += ppSize;

        vi = projected;
    }
}

bool CInscribedShape::isInsidePerimeter(LDPoint testPoint)
{
    for (auto it = nonSequentialPerimeterPoints.begin(); std::next(it) != nonSequentialPerimeterPoints.end(); it++++)
    {
        if ((testPoint.x >= it->x && testPoint.x <= std::next(it)->x) &&
            (testPoint.y >= it->y && testPoint.y <= std::next(it)->y))
            return true;
    }
    return false;
}


bool CInscribedShape::isInsidePerimeter(CInscribedShape& other)
{
    return std::any_of(other.vertexPoints.begin(), other.vertexPoints.end(), [&](LDPoint& vp)
                { return isInsidePerimeter(vp); });
}


void CInscribedShape::sortPerimeterPoints()
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


void CInscribedShape::assignVertexIndexes()
{
    int ppSize = perimeterPoints.size();
    double smallestSubDivison, currentSubDivision;
    smallestSubDivison = currentSubDivision = 1.0 / numVertices;
    
    vertexIndecies.reserve(numVertices);
    vertexIndecies.push_back(ppSize - 1);
    
    for (int i = 0; i < numVertices - 1; i++)
    {
        vertexIndecies.push_back(static_cast<int>(ppSize * currentSubDivision));
        currentSubDivision += smallestSubDivison;
    }
    
}

void CInscribedShape::updateVertexPoints()
{
    vertexPoints.clear();
    
    for (int i = 0; i < numVertices; i++)
    {
        vertexPoints.push_back(perimeterPoints[vertexIndecies[i]]);
    }
    
    vertexPoints.push_back(perimeterPoints[vertexIndecies[0]]);

}

void CInscribedShape::handleKeyStates(const Uint8*& keystates)
{
    if (keystates[SDL_SCANCODE_A])
        rotate(2);

    else if (keystates[SDL_SCANCODE_D])
        rotate(-2);
}
