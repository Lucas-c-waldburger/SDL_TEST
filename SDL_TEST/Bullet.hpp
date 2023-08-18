
#ifndef Bullet_hpp
#define Bullet_hpp

#include "CircleDraw.hpp"
#include "Utils.hpp"
#include "Time.hpp"

using namespace Utils;

const int BULLET_HEIGHT = 5, BULLET_WIDTH = 5;
const int BULLET_SPEED = 3;
const int WAIT_BETWEEN_BULLET = 300;

struct Bullet : public SDL_Rect
{
    Bullet(std::vector<LDPoint> currentBulletPathProjection);

    std::vector<LDPoint> path;
    int pathIndex;
    bool markedDestroy;

    void updateRectXY();
};

struct BulletGenerator
{
    BulletGenerator(SDL_Renderer*& pRenderer);
    std::vector<Bullet> bullets;
    SDL_Renderer*& pRendererRef;
    Time time;

    void makeBullet(std::vector<LDPoint> currentBulletPathProjection); // SEE IF CAN PASS VECTOR BY REFERENCE INSTEAD
    void drawAll();
//    void eraseMarked();
};

#endif /* Bullet_hpp */
