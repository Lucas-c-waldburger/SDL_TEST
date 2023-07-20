
#ifndef CircleDraw_hpp
#define CircleDraw_hpp

#include "Utils.hpp"

using namespace Utils;


const int RESIZE_RATE = 3;

class CircleDraw
{
public:
    CircleDraw(SDL_Renderer* renderer, int r, LDPoint c);
    ~CircleDraw();

    LDPoint center;
    int radius;
    std::vector<LDPoint> perimeterPoints;


    void move(LDPoint amount);
    void recenter();
    void resize(int newRadius);

    void draw();
    void drawFill(SDL_Color col);

    int decideNext(int prevDecisionP, LDPoint prevPoint);
    void reflectAndStore(LDPoint p);
    void findPerimeterPoints();

    bool isInsidePerimeter(LDPoint testPoint);


    void logPerimeterPoints();


    void handleEvent(SDL_Event* e);

protected:
    SDL_Renderer* rendererCpy;

};
#endif /* CircleDraw_hpp */
