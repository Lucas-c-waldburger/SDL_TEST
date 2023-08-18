
#ifndef Asteroid_hpp
#define Asteroid_hpp

#include <random>
#include "CInscribedShape.hpp"
#include "Time.hpp"
#include "Ship.hpp"

const int MIN_ASTEROID_RADIUS = 40, MAX_ASTEROID_RADIUS_ADDITION = 20, STARTING_NUM_VERTICIES = 7;
const int STARTING_ASTEROID_SPEED = 1, STARTING_WAIT_BETWEEN_ASTEROID_SPAWN = 3000, STARTING_MAX_ASTEROIDS_ON_SCREEN = 10;

struct Asteroid : public CInscribedShape
{
    Asteroid(SDL_Renderer*& renderer, int r, LDPoint c, int numVerts);

    std::vector<LDPoint> path;
    int pathIndex;
    bool markedDestroy;
    
    LDPoint randomizeStartingPerimeterPoint();
    void moveForward(int speed);

};


struct AsteroidGenerator
{
//public:
    AsteroidGenerator(SDL_Renderer* renderer);
    ~AsteroidGenerator();
    
    Time spawnTime;
    
    void drawAll();
    void handleSpawn();
    
    const int getSpeed();
    void setSpeed(int newSpeed);
    const int getNumDestroyed();
    void addToNumDestroyed(int amount);
    
//    void increaseDifficulty();
    
//private:
    SDL_Renderer* pRenderer;
    
    std::vector<Asteroid> asteroids;
    
    int asteroidRadius;
    int asteroidNumVertices;
    int asteroidSpeed;
    int waitBetweenSpawn;
    int maxAsteroidsOnScreen;
    
    int numDestroyed;
    
    LDPoint randomizeCenter();
    int randomizeRadius();
    void makeAsteroid();
};



#endif /* Asteroid_hpp */
