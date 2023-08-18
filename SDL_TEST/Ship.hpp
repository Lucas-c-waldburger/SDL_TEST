
#ifndef Ship_hpp
#define Ship_hpp

#include "CInscribedShape.hpp"
#include "Bullet.hpp"
#include "PathPoints.hpp"
#include "VelocityTime.hpp"
// TODO
    // Organize path generation
        // clearly deliniate forward PP creation, backward PP creation, bullet PP creation.
        // bundle cleanly into one function

const int SHIP_INDEX_MOVE_PER_FRAME = 2;

class Ship : public CInscribedShape
{
public:
    Ship(SDL_Renderer* renderer, int r, LDPoint c);
    
    BulletGenerator bulletGenerator;
    
    bool markedDestroy;
    bool markedRecalculatePath;
    
    void draw(); //override;
    void rotate(int amount); //override;
    void goForward();
    
    LDPoint getHead();
    
    
    void updateShipPath();
    
    void handleKeyStates(const Uint8*& keystates);
    
private:
    PathPoints::Path path;
    int currentPathIndex;
    
    VelocityTime velocityTime;
};





//class Ship : public CInscribedTriangle
//{
//public:
//    Ship(SDL_Renderer* renderer, int r, LDPoint c);
//
//    BulletGenerator bulletGenerator;
//    bool markedDestroy;
//    bool markedRecalculatePathPoints;
//
//    void draw() override;
//    void rotate(int amount) override;
//    void goForward() override;
//
//    void generateForwardPathPoints() override;
//    void generateOnlyBulletPathPoints();
//    void generateBackwardsPathPoints();
//    void joinPathPoints();
//
//    void handleKeyStates(const Uint8*& keystates) override;
//
//private:
//    std::vector<LDPoint> backwardsPathPoints;
//    std::vector<LDPoint> tempBulletPathPoints;
//
//    void clipToBulletPathPoints();
//};





#endif /* Ship_hpp */
