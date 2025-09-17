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

bool board::verifyMatch(int& points)
{
    bool ismatch = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool colMatch = (j >= 2 && boardMatrix[i][j] == boardMatrix[i][j - 1] && boardMatrix[i][j] == boardMatrix[i][j - 2]);
            bool rowMatch = i >= 2 && boardMatrix[i][j] == boardMatrix[i - 1][j] && boardMatrix[i][j] == boardMatrix[i - 2][j];
            if (colMatch)
            {
                boardMatrix[i][j] = rand() % gemType, points++;
                boardMatrix[i][j - 1] = rand() % gemType, points++;
                boardMatrix[i][j - 2] = rand() % gemType, points++;
                ismatch = true;
            }

            if (rowMatch)
            {
                boardMatrix[i][j] = rand() % gemType, points++;
                boardMatrix[i - 1][j] = rand() % gemType, points++;
                boardMatrix[i - 2][j] = rand() % gemType, points++;
                ismatch = true;
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
    if (isAdjacentSameRow)
        return true;

    bool isAdjacentSameCol = colFirstClick == colSecondClick && (rowFirstClick == rowSecondClick + 1 || colSecondClick == rowSecondClick - 1);
    if (isAdjacentSameCol)
        return true;

    return false;
}

void board::swapGems(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick)
{
    swap(boardMatrix[rowFirstClick][colFirstClick], boardMatrix[rowSecondClick][colSecondClick]);
}
