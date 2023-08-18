
#include "ScoreBox.hpp"

ScoreDisplay::ScoreBoard::ScoreBoard(SDL_Renderer* renderer) : pRenderer(renderer), totalScore(0)
{};

ScoreDisplay::ScoreBoard::~ScoreBoard()
{
    pRenderer = nullptr;
}

const int ScoreDisplay::ScoreBoard::getTotalScore()
{
    return totalScore;
}

void ScoreDisplay::ScoreBoard::setTotalScore(int newScore)
{
    totalScore = newScore;
}

std::pair<int, int> ScoreDisplay::ScoreBoard::separateScore()
{
    return std::make_pair((totalScore / 10) % 10, totalScore % 10);
}


void ScoreDisplay::ScoreBoard::draw()
{
    SDL_SetRenderDrawColor(pRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    
    std::pair<int, int> separatedScore = separateScore();
    
    for (auto& seg : ScoreDisplay::numberMap[separatedScore.first])
    {
        SDL_RenderDrawLine(pRenderer, seg.first.x - X_SHIFT_FOR_TENS, seg.first.y, seg.second.x - X_SHIFT_FOR_TENS, seg.second.y);
    }
    
    for (auto& seg : ScoreDisplay::numberMap[separatedScore.second])
    {
        SDL_RenderDrawLine(pRenderer, seg.first.x, seg.first.y, seg.second.x, seg.second.y);
    }
}

