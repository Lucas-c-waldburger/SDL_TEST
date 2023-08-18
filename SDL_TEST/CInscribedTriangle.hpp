
#ifndef CInscribedTriangle_hpp
#define CInscribedTriangle_hpp

#include "CircleDraw.hpp"
#include "Bullet.hpp"

const int PIXELS_MOVE_PER_FRAME = 3, ROTATION_RATE = 2;

// PROBABLY RIP ALL MATH OUT OF THESE AND MAKE A TRUE BASE CLASS OUT OF THE ORIGINAL PERIMTER FINDING
class CInscribedTriangle : public CircleDraw
{
public:
    CInscribedTriangle(SDL_Renderer* renderer, int r, LDPoint c);

    virtual void init();
    virtual void draw();
    virtual void rotate(int amount);
    virtual void goForward();

    void sortPerimeterPoints();
    void assignTrianglePointIndexes();
    virtual void generateForwardPathPoints();
    
    LDPoint getHead();

    LDPoint extendLinePoint(LDPoint& A, LDPoint& B, int distance);
    std::vector<LDPoint> clipForwardPathFromHead();
    
    bool pointWithinBounds(LDPoint& p);

    virtual void handleKeyStates(const Uint8*& keystates);

protected:
    LDPoint trianglePoints[4];
    std::vector<int> trianglePointIndexes;
    std::vector<LDPoint> forwardPathPoints;
    int currentForwardPathIndex;

    void updateTranglePoints();
};
#endif /* CInscribedTriangle_hpp */
