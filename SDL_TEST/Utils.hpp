
#ifndef Utils_hpp
#define Utils_hpp

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>

const int SCREEN_WIDTH = 1344, SCREEN_HEIGHT = 756;

namespace Utils
{

    struct LDPoint : public SDL_Point
    {
        LDPoint() : SDL_Point() {};
        LDPoint(int xPos, int yPos) : SDL_Point() { x = xPos; y = yPos; };
        LDPoint(const LDPoint& other) { x = other.x; y = other.y; };

        bool operator==(const LDPoint& other) const { return this->x == other.x && this->y == other.y; }
        bool operator!=(const LDPoint& other) const { return this->x != other.x || this->y != other.y; }

        bool operator<(const LDPoint& other) const { return this->x < other.x && this->y < other.y; }
        bool operator>(const LDPoint& other) const { return this->x > other.x && this->y > other.y; }
        bool operator>=(const LDPoint& other) const { return this->x >= other.x && this->y >= other.y; }
        
        LDPoint operator+(int i) { return LDPoint{ this->x + i, this->y + i}; }
        LDPoint operator-(int i) { return LDPoint{ this->x - i, this->y - i}; }
        LDPoint operator-(LDPoint& other) { return LDPoint{ this->x - other.x, this->y - other.y }; }

        void operator+=(LDPoint& other) { this->x += other.x; this->y += other.y; };

        friend std::ostream& operator<<(std::ostream& stream, LDPoint& p) { stream << p.x << ", " << p.y; return stream; };

    };

    template <typename LDPoint>
    void logPoints(typename std::vector<LDPoint>::iterator it1, typename std::vector<LDPoint>::iterator it2)
    {
        for (; it1 != it2; it1++)
            SDL_Log("(%i, %i)", it1->x, it1->y);
    }


    struct MousePosLog
    {
        MousePosLog() : current(LDPoint{}), last(LDPoint{}) {}
        LDPoint current, last;

        void update()
        {
            SDL_GetMouseState(&current.x, &current.y);
        }

        bool moved()
        {
            return (current == last) ? false : true;
        }

        void log()
        {
            SDL_Log("x: %i , y: %i", current.x, current.y);
        }
    };

    struct LDLine
    {
        LDLine(LDPoint start, LDPoint end) : start(start), end(end), color({ 0, 255, 0 }), intersecting(false) {};

        LDPoint start, end;
        SDL_Color color;
        bool intersecting;

    };


    struct LDIntersect
    {
        int pointDirection(LDPoint p, LDPoint q, LDPoint r)
        {
            std::cout << "Point p = (" << p.x << ", " << p.y << ")\n"
                << "Point q = (" << q.x << ", " << q.y << ")\n"
                << "Point r = (" << r.x << ", " << r.y << ")\n";
            return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        }

        bool linesCollinear(LDLine& line1, LDLine& line2)
        {
            return pointDirection(line1.start, line1.end, line2.start) == 0;
        }

        bool collinearAndOverlap(LDLine& line1, LDLine& line2)
        {
            if (linesCollinear(line1, line2))
            {
                return (line2.start.x <= std::max(line1.start.x, line1.end.x) &&
                    line2.start.x >= std::min(line1.start.x, line1.end.x) &&
                    line2.start.y <= std::max(line1.start.y, line1.end.y) &&
                    line2.start.y >= std::min(line1.start.y, line1.end.y));
            }
            return false;
        }

        bool linesIntersect(LDLine& line1, LDLine& line2)
        {
            // get orientations of line segment start/end points
            int d1 = pointDirection(line1.start, line1.end, line2.start);
            int d2 = pointDirection(line1.start, line1.end, line2.end);
            int d3 = pointDirection(line2.start, line2.end, line1.start);
            int d4 = pointDirection(line2.start, line2.end, line1.end);
            std::cout << "d1 = " << d1 << '\n'
                << "d2 = " << d2 << '\n'
                << "d3 = " << d3 << '\n'
                << "d4 = " << d4 << '\n';
            // first intersect check
            auto directionsDiffer = [&](int firstD, int secondD) { return (firstD > 0 && secondD < 0) || (firstD < 0 && secondD > 0); };

            if (directionsDiffer(d1, d2) && directionsDiffer(d3, d4))
                return true;

            // failed first check, asses if collinear and overlapping
            return (collinearAndOverlap(line1, line2) || collinearAndOverlap(line2, line1)) ? true : false;
        }

        bool operator()(LDLine& line1, LDLine& line2)
        {
            return linesIntersect(line1, line2);
        }
    };

    struct LinePoints
    {

        static LDPoint extendLine(const LDPoint& A, const LDPoint& B, int distance)
        {
            LDPoint C;

            double lenAB = sqrt(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));

            C.x = A.x + (distance * (B.x - A.x) / lenAB);
            C.y = A.y + (distance * (B.y - A.y) / lenAB);

            return C;
        }


        static bool pointWithinScreenBounds(const LDPoint& p)
        {
            return ((p.x >= 0 && p.x <= SCREEN_WIDTH) &&
                (p.y >= 0 && p.y <= SCREEN_HEIGHT));
        }
        

        static void generateLinePointsToEdge(const LDPoint& A, const LDPoint& B, std::vector<LDPoint>& pathPoints, int distanceBetweenPixels = 2)
        {
            int i = 0;
            LDPoint projectedPoint = extendLine(A, B, i);
            while (pointWithinScreenBounds(projectedPoint))
            {
                pathPoints.push_back(projectedPoint);
                i += distanceBetweenPixels;
                projectedPoint = extendLine(A, B, i);
            }
        }
    };


};


#endif /* Utils_hpp */
