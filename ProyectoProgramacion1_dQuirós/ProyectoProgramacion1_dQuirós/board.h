#pragma once
#include "gem.h"
const int rows = 8;
const int cols = 8;
const int pixelSize = 70;
const int gemType = 5;
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
    bool verifyMatch(int& points);// CHECK: debe seguir el estandar de nombres para funciones booleanas
    void drawGemSprites(sf::RenderWindow& window);

    bool isAdjacent(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);
    void swapGems(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);

};


