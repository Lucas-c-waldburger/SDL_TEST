
#ifndef Bullet_hpp
#define Bullet_hpp

#include "CircleDraw.hpp"
#include "Utils.hpp"
#include "Time.hpp"

using namespace Utils;

const int BULLET_HEIGHT = 5, BULLET_WIDTH = 5;
const int BULLET_SPEED = 2;
const int WAIT_BETWEEN_BULLET = 300;

struct Bullet : public SDL_Rect
{
    Bullet(std::vector<LDPoint> currentForwardPathProjection);

    std::vector<LDPoint> forwardPathProjection;
    int pathIndex;
    bool active;

    void updateRectXY();
};

struct BulletGenerator
{
    BulletGenerator(SDL_Renderer*& pRenderer);
    std::vector<Bullet> bullets;
    SDL_Renderer*& pRendererRef;
    Time time;

    void makeBullet(std::vector<LDPoint> currentForwardPathProjection);
    void drawAll();
};

#endif /* Bullet_hpp */
