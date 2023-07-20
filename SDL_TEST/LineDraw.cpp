
#include "LineDraw.hpp"

LineDraw::LineDraw(SDL_Renderer* renderer) : rendererCpy(renderer)
{}

LineDraw::~LineDraw()
{
    rendererCpy = nullptr;
}


void LineDraw::setNewPoint()
{
    points.emplace_back(LDPoint{});
    SDL_GetMouseState(&points.back().x, &points.back().y);
}


int LineDraw::numPoints()
{
    return points.size();
}


void LineDraw::addLine(LDPoint start, LDPoint end)
{
    LDLine newLine{ start, end };

    if (lines.size() > 0)
    {
        checkIntersecting(newLine);
    }

    lines.push_back(newLine);
}


void LineDraw::checkIntersecting(LDLine& newLine)
{
    LDIntersect ldIntersect;

    std::for_each(lines.begin(), lines.end(), [&](LDLine& ldLine)
        {
            if (!newLine.intersecting || !ldLine.intersecting) // if either of the lines weren't marked intersecting
            {
                if (ldIntersect(newLine, ldLine)) // if the new line and comparator line do intersect, change to true and make color red
                {
                    newLine.intersecting = ldLine.intersecting = true;
                    newLine.color = ldLine.color = SDL_Color{ 255, 0, 0 };
                }
            }
        });

    if (!newLine.intersecting)
    {
        newLine.color = SDL_Color{ 0, 255, 0 };
    }
}


void LineDraw::show()
{
    if (mousePos.last != points.back())
    {
        mousePos.last = points.back();
    }
    mousePos.update();

    SDL_SetRenderDrawColor(rendererCpy, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(rendererCpy, mousePos.last.x, mousePos.last.y, mousePos.current.x, mousePos.current.y);
}


//void LineDraw::drawLinked()
//{
//    SDL_SetRenderDrawColor(rendererCpy, 0x00, 0x00, 0x00, 0xFF);
//
//    for (auto it = points.begin(); std::next(it) != points.end(); it++)
//    {
//        SDL_RenderDrawLine(rendererCpy, it->x, it->y, std::next(it)->x, std::next(it)->y);
//        addLine(*it, *(std::next(it)));
//    }
//}

void LineDraw::draw()
{
    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        SDL_SetRenderDrawColor(rendererCpy, it->color.r, it->color.g, it->color.b, 0xFF);

        SDL_RenderDrawLine(rendererCpy, it->start.x, it->start.y, it->end.x, it->end.y);
    }
}


void LineDraw::handleEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN)
    {
        setNewPoint();

        if (points.size() > 1)
        {
            addLine(points.front(), points.back());
            points.clear();
        }
    }
}

