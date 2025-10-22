#pragma once
#include "gem.h"
const int rows = 8;
const int cols = 8;
const int pixelSize = 70;
const int gemType = 5;
const int minStreakValues = 3;

class board
{
private:
    int boardMatrix[rows][cols];
    gem gemTextures[gemType];    
    sf::Sprite sprites[rows][cols];

public:
    void fillBoard();
    void createGemTextures();
    void createGemSprites();
    void drawGemSprites(sf::RenderWindow& window);
    bool isVerifyMatch(int targetColor, int& currentCount, int& points);

    bool isAdjacent(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);
    void swapGems(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);

    void verifyHorizontalStreak(int firstRow, int firstCol,
        int targetColor, int& currentCount,
        int& points, bool& isMatch);
    void verifyVerticalStreak(int firstRow, int firstCol,
        int targetColor, int& currentCount,
        int& points, bool& isMatch);

   
    bool applyGravity();
    void fillEmptyCells();

};


