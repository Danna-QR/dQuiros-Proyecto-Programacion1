#include "board.h"
#include "gem.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void board::fillBoard()
{
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            boardMatrix[i][j] = rand() % gemType;
        }
    }
}

void board::createGemTextures()
{
    gemTextures[0].setType(0, "assets/gemaRoja.png");
    gemTextures[1].setType(1, "assets/gemaVerde.png");
    gemTextures[2].setType(2, "assets/gemaAzul.png");
    gemTextures[3].setType(3, "assets/gemaAmarilla.png");
    gemTextures[4].setType(4, "assets/gemaMorada.png");
}

void board::createGemSprites()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            sf::Texture& spriteTexture = gemTextures[boardMatrix[i][j]].getTexture();

            sprites[i][j].setTexture(spriteTexture);
            sprites[i][j].setPosition(j * pixelSize, i * pixelSize);
            sprites[i][j].setScale(
                pixelSize / (float)(spriteTexture).getSize().x,
                pixelSize / (float)(spriteTexture).getSize().y);
        }
    }
}

bool board::isVerifyMatch(int targetColor, int& currentCount, int& points)
{
    bool ismatch = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            bool colMatch = (i >= minStreakValues && boardMatrix[i][j] != -1 &&
                boardMatrix[i][j] == boardMatrix[i - 1][j] &&
                boardMatrix[i][j] == boardMatrix[i - 2][j]);

            bool rowMatch = (j >= minStreakValues && boardMatrix[i][j] != -1 &&
                boardMatrix[i][j] == boardMatrix[i][j - 1] &&
                boardMatrix[i][j] == boardMatrix[i][j - 2]);

            if (colMatch && rowMatch) {
                processVerticalStreak(i, j, targetColor, currentCount, points, isMatch);
                processHorizontalStreak(i, j, targetColor, currentCount, points, isMatch);
            }
            else if (colMatch) {
                processVerticalStreak(i, j, targetColor, currentCount, points, isMatch);
            }
            else if (rowMatch) {
                processHorizontalStreak(i, j, targetColor, currentCount, points, isMatch);
            }
        }
    }
    return ismatch;
}


void board::drawGemSprites(sf::RenderWindow& window)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            window.draw(sprites[i][j]);
        }
    }
}

bool board::isAdjacent(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick)
{
    bool isAdjacentSameRow = rowFirstClick == rowSecondClick && (colFirstClick == colSecondClick + 1 || colFirstClick == colSecondClick - 1);
    if (isAdjacentSameRow)// CHECK: Los if deben tener brackets
        return true;

    bool isAdjacentSameCol = colFirstClick == colSecondClick && (rowFirstClick == rowSecondClick + 1 || colSecondClick == rowSecondClick - 1);
    if (isAdjacentSameCol)// CHECK: Los if deben tener brackets
        return true;

    return false;
}

void board::swapGems(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick)
{
    swap(boardMatrix[rowFirstClick][colFirstClick], boardMatrix[rowSecondClick][colSecondClick]);
}
