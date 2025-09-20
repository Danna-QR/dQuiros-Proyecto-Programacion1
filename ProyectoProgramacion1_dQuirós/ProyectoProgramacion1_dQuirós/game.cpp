#include "game.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


void game::showPrincipalWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Match - 3", sf::Style::Close);

    bool openBoardWindow = false;// CHECK: debe seguir el estandar de nombres para variables booleanas

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("assets/play.png")) {
        cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite button(buttonTexture);
    button.setPosition(350.f, 510.f);
    button.setScale(0.3f, 0.3f);

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
            // CHECK: Código muy anidado, máximo 3 anidaciones
            if (event.type == sf::Event::Closed)// CHECK: Los if deben tener brackets
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
    int totalPoints = points * 10;
    pointsText.setString("Puntos: " + std::to_string(totalPoints));
}

void game::processMatches()
{
    while (board.verifyMatch(points)) {
        board.createGemSprites();
    }
}

void game::handleMove()
{
    board.swapGems(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick);
    board.createGemSprites();
    std::cout << "Intercambio realizado!\n";

    if (!board.verifyMatch(points)) {
        board.swapGems(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick);

        std::cout << "No hubo match, intercambio revertido.\n";
    }

    else {
        decreaseMovements(movements);
        sumPoints(points);
        processMatches();
    }
    board.createGemSprites();
    firstClick = true;
}

void game::handleMouseClick(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!mousePressed) { 
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            int currentCol = mousePosition.x / pixelSize;
            int currentRow = mousePosition.y / pixelSize;
            // CHECK: Código muy anidado, máximo 3 anidaciones
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
                        handleMove(); 
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
    if (!backgroundTexture.loadFromFile("assets/backroundImage.png")) {
        std::cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite background(backgroundTexture);

    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );


    if (!font.loadFromFile("assets/ELEGANT TYPEWRITER Regular.ttf")) {
        std::cout << "Error: no se pudo cargar la fuente\n";
    }

    movementText.setFont(font);
    movementText.setCharacterSize(30);
    movementText.setFillColor(sf::Color::White);
    movementText.setString("Movimientos: \n " + to_string(movements) + " \n ");

    pointsText.setFont(font);
    pointsText.setCharacterSize(30);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setString(" \n Puntos: \n " + to_string(points));

    movementText.setPosition(
        window.getSize().x - movementText.getLocalBounds().width - 35, 60.f);

    pointsText.setPosition(
        window.getSize().x - pointsText.getLocalBounds().width - 55, 150.f + 100);


    board.createGemTextures();
    board.fillBoard();
    board.verifyMatch(points);
    processMatches();
    board.createGemSprites();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)// CHECK: Los if deben tener brackets
                window.close();
        }
        handleMouseClick(window);
        window.clear();
        window.draw(background);
        window.draw(pointsText);
        window.draw(movementText);
        board.drawGemSprites(window);
        window.display();
    }
}

void game::showFinalWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FinalWindow", sf::Style::Close);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/backroundImage.png")) {
        std::cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite background(backgroundTexture);

    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );



    sf::Font font;
    if (!font.loadFromFile("assets/ELEGANT TYPEWRITER Regular.ttf")) {
        std::cout << "Error cargando fuente.\n";
    }

    sf::Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(50);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString("Puntaje final: " + std::to_string(points));
    finalScoreText.setPosition(210.f, 70.f);

    sf::Texture restartTexture;
    if (!restartTexture.loadFromFile("assets/playAgain.png")) {
        std::cout << "Error cargando imagen restart.png\n";
    }

    sf::Texture exitTexture;
    if (!exitTexture.loadFromFile("assets/exit.png")) {
        std::cout << "Error cargando imagen exit.png\n";
    }

    sf::Sprite restartButton(restartTexture);
    restartButton.setPosition(130.f, 350.f);
    restartButton.setScale(0.5f, 0.5f); 

    sf::Sprite exitButton(exitTexture);
    exitButton.setPosition(500.f, 350.f);
    exitButton.setScale(0.5f, 0.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // CHECK: Código muy anidado, máximo 3 anidaciones
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();

                    points = 0;
                    movements = 20;
                    board.fillBoard();
                    processMatches();
                    board.createGemSprites();
                    showBoardWindow();
                }

                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    exit(0);
                }
            }
        }

        window.clear();
        window.draw(background);;
        window.draw(finalScoreText);
        window.draw(restartButton);
        window.draw(exitButton);
        window.display();
    }
}


