
#include "Bullet.hpp"

Bullet::Bullet(std::vector<LDPoint> currentForwardPathProjection) : forwardPathProjection(currentForwardPathProjection), pathIndex(0), active(true)
{
    updateRectXY();
    w = BULLET_WIDTH;
    h = BULLET_HEIGHT;

}

void Bullet::updateRectXY()
{
    x = forwardPathProjection[pathIndex].x;
    y = forwardPathProjection[pathIndex].y;
}


BulletGenerator::BulletGenerator(SDL_Renderer*& pRenderer) : pRendererRef(pRenderer), time(Time{})
{}


void BulletGenerator::makeBullet(std::vector<LDPoint> currentForwardPathProjection)
{
    if (currentForwardPathProjection.size() > 0)
    {
        bullets.emplace_back(currentForwardPathProjection);
        time.setWait(WAIT_BETWEEN_BULLET);
    }
}

void BulletGenerator::drawAll()
{
    SDL_SetRenderDrawColor(pRendererRef, 255, 0, 0, 255);
    
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (it->pathIndex >= it->forwardPathProjection.size() - 1)
        {
            it = bullets.erase(it);
        }
        else
        {
            it->pathIndex += BULLET_SPEED;
            it->updateRectXY();
            SDL_RenderFillRect(pRendererRef, &(*it));
            ++it;
        }
    }
}
