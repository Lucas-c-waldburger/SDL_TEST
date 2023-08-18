
#include "Asteroid.hpp"


Asteroid::Asteroid(SDL_Renderer*& renderer, int r, LDPoint c, int numVerts) : CInscribedShape(renderer, r, c, numVerts), pathIndex(1), markedDestroy(false)
{
    LinePoints::generateLinePointsToEdge(center, randomizeStartingPerimeterPoint(), path, 1);
}


LDPoint Asteroid::randomizeStartingPerimeterPoint()
{
    int randIndex = rand() % perimeterPoints.size();
    LDPoint randomizedPerimeterPoint = perimeterPoints[randIndex];
    
    while (!LinePoints::pointWithinScreenBounds(randomizedPerimeterPoint))
    {
        randIndex = rand() % perimeterPoints.size();
        randomizedPerimeterPoint = perimeterPoints[randIndex];
    }
    
    return randomizedPerimeterPoint;
}

void Asteroid::moveForward(int speed)
{
    LDPoint& nextPoint = path[pathIndex];
    move(nextPoint - center);
    rotate(1);
    pathIndex += speed;
}



AsteroidGenerator::AsteroidGenerator(SDL_Renderer* renderer) : pRenderer(renderer), asteroidRadius(MIN_ASTEROID_RADIUS), asteroidNumVertices(STARTING_NUM_VERTICIES),
                                     asteroidSpeed(STARTING_ASTEROID_SPEED), waitBetweenSpawn(STARTING_WAIT_BETWEEN_ASTEROID_SPAWN), maxAsteroidsOnScreen(STARTING_MAX_ASTEROIDS_ON_SCREEN), numDestroyed(0)
{
    std::srand(SDL_GetTicks());
}

AsteroidGenerator::~AsteroidGenerator()
{
    pRenderer = nullptr;
}

LDPoint AsteroidGenerator::randomizeCenter()
{
    LDPoint center{0, 0};
    int alongX = 0;

    auto randXBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_WIDTH; };
    auto randYBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_HEIGHT; };
    auto randXPoint = []() { return (rand() % (SCREEN_WIDTH + 1)); };
    auto randYPoint = []() { return (rand() % (SCREEN_HEIGHT + 1)); };
    
    int xOrYStart = rand() % 2;
    
    if (xOrYStart == alongX)
    {
        center.x = randXBound();
        center.y = randYPoint();
//        std::cout << "RAND Y POINT: " << center.y << '\n';
    }
    else
    {
        center.x = randXPoint();
        center.y = randYBound();
//        std::cout << "RAND X POINT: " << center.x << '\n';

    }
    
//    std::cout << "CENTER: " << center;
    return center;
}

int AsteroidGenerator::randomizeRadius()
{
    return MIN_ASTEROID_RADIUS + (rand() % (MAX_ASTEROID_RADIUS_ADDITION + 1));
}

//std::pair<LDPoint, LDPoint> AsteroidGenerator::generatePathEndpoints()
//{
//    LDPoint start, end;
//    int alongX = 0, alongY = 1;
//
//    auto randXBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_WIDTH; };
//    auto randYBound = []() { return (rand() % 2 == 0) ? 0 : SCREEN_HEIGHT; };
//    auto randXPoint = []() { return (rand() % (SCREEN_WIDTH + 1)); };
//    auto randYPoint = []() { return (rand() % (SCREEN_HEIGHT + 1)); };
//
//    int xOrYStart = rand() % 2, xOrYEnd = rand() % 2;
//
//    if (xOrYStart == alongX)
//    {
//        start.x = randXBound();
//        start.y = randYPoint();
//    }
//    else
//    {
//        start.x = randXPoint();
//        start.y = randYBound();
//    }
//
//    if (xOrYEnd == alongX) // if we're leaving along x bounds
//    {
//        if (xOrYStart == alongX) // if we're also entering from X bounds
//        {
//            end.x = (start.x == 0) ? SCREEN_WIDTH : 0; // make sure we're leaving on the opposite screen side
//            end.y = randYPoint();
//        }
//        else // leaving from Y bounds
//            end.x = randXPoint();
//            end.y = randYBound();
//    }
//    else // leaving along Y bounds
//    {
//        if (xOrYStart == alongY) // if we're also entering from Y bounds
//        {
//            end.x = randXPoint();
//            end.y = (start.y == 0) ? SCREEN_HEIGHT : 0; // make sure we're leaving on the opposite screen top/bot
//        }
//        else // leaving from X bounds
//            end.x = randXBound();
//            end.y = randYPoint();
//    }
////    std::cout << start << '\n' << end;
//    return std::make_pair(start, end);
//}

void AsteroidGenerator::makeAsteroid()
{
    int randomRadius = randomizeRadius();
//    std::cout << "RANDOM RADIUS: " << randomRadius << '\n';
    asteroids.emplace_back(pRenderer, randomRadius, randomizeCenter(), asteroidNumVertices);
}

void AsteroidGenerator::drawAll()
{
//    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
    
    handleSpawn();
    
    for (auto it = asteroids.begin(); it != asteroids.end(); it++)
    {

        it->moveForward(asteroidSpeed);
        it->draw();
    }
}

void AsteroidGenerator::handleSpawn()
{
    if (spawnTime.waitOver() && asteroids.size() < maxAsteroidsOnScreen)
    {
        makeAsteroid();
        spawnTime.setWait(waitBetweenSpawn);
    }
}


const int AsteroidGenerator::getSpeed()
{
    return asteroidSpeed;
}


void AsteroidGenerator::setSpeed(int newSpeed)
{
    asteroidSpeed = newSpeed;
}

const int AsteroidGenerator::getNumDestroyed()
{
    return numDestroyed;
}


void AsteroidGenerator::addToNumDestroyed(int amount)
{
    numDestroyed += amount;
//    increaseDifficulty();
}

void AsteroidGenerator::increaseDifficulty()
//{
//    if (numDestroyed > 10)
//        asteroidSpeed = 2;
//    if (numDestroyed > 20)
//        asteroidSpeed = 3;
//    
//    waitBetweenSpawn -= 1;
//    maxAsteroidsOnScreen += 1;
//    
//};
