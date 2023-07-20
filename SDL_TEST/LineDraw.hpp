
#ifndef LineDraw_hpp
#define LineDraw_hpp

#include "Utils.hpp"

using namespace Utils;


class LineDraw
{
public:
    LineDraw(SDL_Renderer* renderer);
    ~LineDraw();

    MousePosLog mousePos;
    std::vector<LDPoint> points;
    std::vector<LDLine> lines;

    void setNewPoint();
    int numPoints();

    void addLine(LDPoint start, LDPoint end);
    void checkIntersecting(LDLine& newLine);

    void show();
    void draw();

    void handleEvent(SDL_Event* e);

private:
    SDL_Renderer* rendererCpy;
};

#endif /* LineDraw_hpp */
