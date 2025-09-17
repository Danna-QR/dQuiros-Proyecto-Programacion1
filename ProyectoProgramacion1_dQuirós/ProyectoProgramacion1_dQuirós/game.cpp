#include "game.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


void game::showPrincipalWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Match - 3", sf::Style::Close);

    bool openBoardWindow = false;

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("assets/play.png")) {
        cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite button(buttonTexture);
    button.setScale(0.5f, 0.5f);//fix

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/principal.jpg")) {
        cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite background(backgroundTexture);

    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    openBoardWindow = true;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(button);
        window.display();

        if (openBoardWindow) {
            window.close();    
            showBoardWindow();  
        }
    }
}


void game::decreaseMovements(int& movements)
{
    if (movements > 0)
    {
        movements--;
        movementText.setString("Movimientos: " + std::to_string(movements));
    }
    if (movements <= 0) {
        showFinalWindow();
    }
}

void game::sumPoints(int& points)
{
    points += 3 * 10;
    pointsText.setString("Puntos: " + std::to_string(points));
}


void game::handleMouseClick(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!mousePressed) { 
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            int currentCol = mousePosition.x / pixelSize;
            int currentRow = mousePosition.y / pixelSize;

            if (currentCol >= 0 && currentCol < cols && currentRow >= 0 && currentRow < rows) {

                if (firstClick) {
                    rowFirstClick = currentRow;
                    colFirstClick = currentCol;
                    firstClick = false;
                }
                else {
                    rowSecondClick = currentRow;
                    colSecondClick = currentCol;

                    if (board.isAdjacent(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick)) {

                        board.swapGems(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick);
                        board.createGemSprites();

                        if (!board.verifyMatch()) {

                            board.swapGems(rowSecondClick, colSecondClick, rowFirstClick, colFirstClick);

                        }
                        else {
                            decreaseMovements(movements);
                            sumPoints(points);
                        }

                        board.createGemSprites(); 
                        firstClick = true;
                        
                    }
                }
            }
            mousePressed = true; 
        }
    }
    else {
        mousePressed = false;
    }
}


void game::showBoardWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Board window", sf::Style::Close);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/unnamed.png")) {
        std::cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite background(backgroundTexture);

    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );


    board.fillBoard();
    board.verifyMatch();
    board.createGemTextures();
    board.createGemSprites();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        handleMouseClick(window);
        window.clear();
        window.draw(background);
        board.drawGemSprites(window);
        window.display();
    }
}

void game::showFinalWindow()
{
}


