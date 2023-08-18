
#include "TempObjectLifetimeManager.hpp"


void ObjectDestructionManager::resolveAll(Ship& ship, AsteroidGenerator& asteroidGenerator)
{
    if (checkShipCollision(ship, asteroidGenerator))
    {
        ship.markedDestroy = true;
        return;
    }
    
    resolveExpirations(ship.bulletGenerator, asteroidGenerator);
    resolveBulletCollisions(ship.bulletGenerator, asteroidGenerator);
}

bool ObjectDestructionManager::collided(Bullet& bullet, Asteroid& asteroid)
{
    return asteroid.isInsidePerimeter(LDPoint{bullet.x, bullet.y});
}
             
template <class T>
int ObjectDestructionManager::checkExpiration(std::vector<T>& objVec) // SEE IF WE CAN RETURN A BOOL TO DETERMINE WHETHER TO RUN ERASE IF ANY WERE MARKED
{
    int numToErase = 0;
    
    std::for_each(objVec.begin(), objVec.end(), [&numToErase](T& obj)
    {
        if (obj.pathIndex >= obj.path.size() - 1)
        {
            obj.markedDestroy = true;
            ++numToErase;
        }
    });
    
    return numToErase;
}

template <class T>
void ObjectDestructionManager::eraseMarked(std::vector<T>& objVec)
{
    objVec.erase(std::remove_if(objVec.begin(), objVec.end(), [](const T& obj) { return obj.markedDestroy; }),
                      objVec.end());
}
        
        
bool ObjectDestructionManager::checkShipCollision(Ship& ship, AsteroidGenerator& asteroidGenerator)
{
    for (auto aIt = asteroidGenerator.asteroids.begin(); aIt != asteroidGenerator.asteroids.end(); aIt++)
    {
        if (aIt->isInsidePerimeter(ship))
        {
            return true;
        }
    }
    
    return false;
}
        

int ObjectDestructionManager::checkBulletCollisions(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator)
{
    int numToErase = 0;
    
    for (auto bIt = bulletGenerator.bullets.begin(); bIt != bulletGenerator.bullets.end(); bIt++)
    {
        for (auto aIt = asteroidGenerator.asteroids.begin(); aIt != asteroidGenerator.asteroids.end(); aIt++)
        {
            if (!aIt->markedDestroy && collided(*bIt, *aIt))
            {
                aIt->markedDestroy = true;
                bIt->markedDestroy = true;
                ++numToErase;
                break;
            }
        }
    }
    
    return numToErase;
}

// DONT NEED TO ADD TO SCORE WITH EXPIRATIONS!
void ObjectDestructionManager::resolveExpirations(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator)
{
    int numBulletsToErase = checkExpiration<Bullet>(bulletGenerator.bullets);
    if (numBulletsToErase > 0)
    {
        eraseMarked<Bullet>(bulletGenerator.bullets);
    }
    
    int numAsteroidsToErase = checkExpiration<Asteroid>(asteroidGenerator.asteroids);
    if (numAsteroidsToErase > 0)
    {
        eraseMarked<Asteroid>(asteroidGenerator.asteroids);
    }
}


void ObjectDestructionManager::resolveBulletCollisions(BulletGenerator& bulletGenerator, AsteroidGenerator& asteroidGenerator)
{
    int numToErase = checkBulletCollisions(bulletGenerator, asteroidGenerator);
    if (numToErase > 0)
    {
        asteroidGenerator.addToNumDestroyed(numToErase);
        eraseMarked<Asteroid>(asteroidGenerator.asteroids);
        
        eraseMarked<Bullet>(bulletGenerator.bullets);
    }
}
