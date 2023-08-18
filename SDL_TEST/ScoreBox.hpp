
#ifndef ScoreBox_hpp
#define ScoreBox_hpp

#include "Asteroid.hpp"
#include <iostream>
#include <unordered_map>


namespace ScoreDisplay
{
    const int SEGMENT_LENGTH = 17, PADDING = 15;
    constexpr int X_SHIFT_FOR_TENS = SEGMENT_LENGTH + PADDING;

    typedef std::unordered_map<int, std::vector<std::pair<LDPoint, LDPoint>>> NumDisplayMap;

    inline const LDPoint SEG_POINTS[6] =
    {
        {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, PADDING},
        {SCREEN_WIDTH - PADDING, PADDING},
        {SCREEN_WIDTH - PADDING, SEGMENT_LENGTH + PADDING},
        {SCREEN_WIDTH - PADDING, (SEGMENT_LENGTH * 2) + PADDING},
        {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, (SEGMENT_LENGTH * 2) + PADDING},
        {SCREEN_WIDTH - SEGMENT_LENGTH - PADDING, SEGMENT_LENGTH + PADDING}
    };


    inline const std::pair<LDPoint, LDPoint> SEG_PAIRS[7] =
    {
        { SEG_POINTS[0], SEG_POINTS[1] }, // TOP       [0]
        { SEG_POINTS[1], SEG_POINTS[2] }, // TOP-RIGHT [1]
        { SEG_POINTS[2], SEG_POINTS[3] }, // BOT-RIGHT [2]
        { SEG_POINTS[3], SEG_POINTS[4] }, // BOT       [3]
        { SEG_POINTS[4], SEG_POINTS[5] }, // BOT-LEFT  [4]
        { SEG_POINTS[5], SEG_POINTS[0] }, // TOP-LEFT  [5]
        { SEG_POINTS[5], SEG_POINTS[2] }, // MID       [6]
    };

    inline std::unordered_map<int, std::vector<std::pair<LDPoint, LDPoint>>> numberMap =
    {
        { 0, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4], SEG_PAIRS[5] } },
        { 1, { SEG_PAIRS[1], SEG_PAIRS[2] } },
        { 2, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[6], SEG_PAIRS[4], SEG_PAIRS[3] } },
        { 3, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[6] } },
        { 4, { SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[6], SEG_PAIRS[5] } },
        { 5, { SEG_PAIRS[0], SEG_PAIRS[5], SEG_PAIRS[6], SEG_PAIRS[2], SEG_PAIRS[3] } },
        { 6, { SEG_PAIRS[0], SEG_PAIRS[5], SEG_PAIRS[6], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4] } },
        { 7, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2] } },
        { 8, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[3], SEG_PAIRS[4], SEG_PAIRS[5], SEG_PAIRS[6] } },
        { 9, { SEG_PAIRS[0], SEG_PAIRS[1], SEG_PAIRS[2], SEG_PAIRS[5], SEG_PAIRS[6] } }
    };


    
    class ScoreBoard
    {
    public:
        ScoreBoard(SDL_Renderer* renderer);
        ~ScoreBoard();
        
        const int getTotalScore();
        void setTotalScore(int newScore);
        
        void draw();
        
        
    private:
        SDL_Renderer* pRenderer;
        
        int totalScore;
        std::pair<int, int> separateScore();
        

    };


}

#endif
