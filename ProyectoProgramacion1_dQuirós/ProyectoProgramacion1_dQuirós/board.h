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
    gem gemTextures[gemType];     // ahora es un array estático
    sf::Sprite sprites[rows][cols];

public:
    void fillBoard();
    void createGemTextures();
    void createGemSprites();
    bool verifyMatch();
    void draw(sf::RenderWindow& window);


    // ?? Nuevas funciones
    bool isAdjacent(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);
    void swapGems(int rowFirstClick, int colFirstClick, int rowSecondClick, int colSecondClick);

};

