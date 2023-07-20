
#include "CircleDraw.hpp"

CircleDraw::CircleDraw(SDL_Renderer* renderer, int r, LDPoint c) : rendererCpy(renderer), radius(r), center(c)
{
    findPerimeterPoints();
    /*move(center);*/
}

CircleDraw::~CircleDraw()
{
    rendererCpy = nullptr;
}

// FIX SO IT TAKES RELATIVE POSIITON INTO ACCOUNT (NOT JUST +=)!!!!
void CircleDraw::move(LDPoint newP)
{
    std::for_each(perimeterPoints.begin(), perimeterPoints.end(), [&newP](LDPoint& p) { p += newP; });
    center += newP;
}

void CircleDraw::recenter()
{
    std::for_each(perimeterPoints.begin(), perimeterPoints.end(), [&](LDPoint& p) { p += center; });
}

void CircleDraw::resize(int newRadius)
{
    radius = newRadius;
    perimeterPoints.clear();
    findPerimeterPoints();
    recenter();
}

void CircleDraw::draw()
{
    SDL_SetRenderDrawColor(rendererCpy, 0, 0, 0, 0xFF);
    SDL_RenderDrawPoints(rendererCpy, &perimeterPoints[0], perimeterPoints.size());
}


void CircleDraw::drawFill(SDL_Color col)
{
    SDL_SetRenderDrawColor(rendererCpy, col.r, col.g, col.b, 0xFF);
    SDL_RenderDrawLines(rendererCpy, &perimeterPoints[0], perimeterPoints.size());
}

int CircleDraw::decideNext(int prevYChangeDecision, LDPoint prevPoint)
{
    int newYChangeDecision = 0;
    LDPoint nextPoint = prevPoint;

    if (prevYChangeDecision < 0)
    {
        nextPoint = LDPoint{ prevPoint.x + 1, prevPoint.y };
        newYChangeDecision = prevYChangeDecision + 4 * prevPoint.x + 6;
    }
    else
    {
        nextPoint = LDPoint{ prevPoint.x + 1, prevPoint.y - 1 };
        newYChangeDecision = prevYChangeDecision + 4 * (prevPoint.x - prevPoint.y) + 10;
    }

    reflectAndStore(LDPoint{ nextPoint.y, nextPoint.x });
    reflectAndStore(nextPoint);

    return newYChangeDecision;
}


void CircleDraw::reflectAndStore(LDPoint p)
{
    perimeterPoints.emplace_back(LDPoint{ -p.x, -p.y });
    perimeterPoints.emplace_back(LDPoint{ p.x, -p.y });
    perimeterPoints.emplace_back(LDPoint{ -p.x, p.y });
    perimeterPoints.emplace_back(LDPoint{ p.x, p.y });
}


void CircleDraw::findPerimeterPoints()
{
    perimeterPoints.emplace_back(LDPoint{ -radius, 0 });
    perimeterPoints.emplace_back(LDPoint{ radius, 0 });
    perimeterPoints.emplace_back(LDPoint{ 0, -radius });
    perimeterPoints.emplace_back(LDPoint{ 0, radius });

    int yChangeDecision = 3 - (2 * radius);

    while (perimeterPoints.back().x < perimeterPoints.back().y)
    {
        yChangeDecision = decideNext(yChangeDecision, perimeterPoints.back());
    }
}

bool CircleDraw::isInsidePerimeter(LDPoint testPoint)
{
    for (auto it = perimeterPoints.begin(); std::next(it) != perimeterPoints.end(); it++++)
    {
        if ((testPoint.x >= it->x && testPoint.x <= std::next(it)->x) &&
            (testPoint.y >= it->y && testPoint.y <= std::next(it)->y))
            return true;
    }
    return false;
}



void CircleDraw::logPerimeterPoints()
{
    for (auto& point : perimeterPoints)
    {
        SDL_Log("(%i, %i)", point.x, point.y);
    }
}

void CircleDraw::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEWHEEL)
    {
        int newRadius = radius;

        if (e->wheel.y > 0)
            newRadius += RESIZE_RATE;

        else if (e->wheel.y < 0)
            newRadius -= RESIZE_RATE;

        resize(newRadius);
    }

    else if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        LDPoint temp;

        SDL_GetMouseState(&temp.x, &temp.y);

        move(temp - center);

        center = temp;
    }
}
