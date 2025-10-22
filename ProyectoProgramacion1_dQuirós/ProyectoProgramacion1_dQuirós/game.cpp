#include "game.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


void game::showPrincipalWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Match - 3", sf::Style::Close);

    bool isOpenBoardWindow = false;

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

}

void game::sumPoints(int& points)
{
    int totalPoints = points * 10;
    pointsText.setString("Puntos: " + std::to_string(totalPoints));
}

void game::processMatches()
{
    while (board.isVerifyMatch(int targetColor, int& currentCount, int& points)) {
        board.createGemSprites();
    }
}

void game::handleMove()
{
    board.swapGems(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick);
    board.createGemSprites();
    std::cout << "Intercambio realizado!\n";

    if (!board.isVerifyMatch(int targetColor, int& currentCount, int& points)) {
        board.swapGems(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick);

        std::cout << "No hubo match, intercambio revertido.\n";
    }

    else {
        decreaseMovements(movements);
        sumPoints(points);
        processMatches();
    }
    board.createGemSprites();
    isFirstClick = true;
}

void game::handleMouseClick(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!isMousePressed) { 
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            int currentCol = mousePosition.x / pixelSize;
            int currentRow = mousePosition.y / pixelSize;
            // CHECK: Código muy anidado, máximo 3 anidaciones
            if (currentCol >= 0 && currentCol < cols && currentRow >= 0 && currentRow < rows) {

                if (isFirstClick) {
                    rowFirstClick = currentRow;
                    colFirstClick = currentCol;
                    isFirstClick = false;
                }
                else {
                    rowSecondClick = currentRow;
                    colSecondClick = currentCol;

                    if (board.isAdjacent(rowFirstClick, colFirstClick, rowSecondClick, colSecondClick)) {
                        handleMove(); 
                    }
                }
            }
            isMousePressed = true;
        }
    }
    else {
        isMousePressed = false;
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
    board.isVerifyMatch(targetGemColor, currentCount, points);
    board.fillBoard(); 
    processMatches();
    board.createGemSprites();
    handleLevels(currentLevel)

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
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

void game::showFinalLevelWindow()
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

   
    sf::Texture nextLevelTexture;
    if (!nextLevelTexture.loadFromFile("assets/nextLevel.jpg")) {
        std::cout << "Error cargando imagen nextLevel.jpg\n";
    }

    sf::Sprite restartButton(restartTexture);
    restartButton.setPosition(130.f, 350.f);
    restartButton.setScale(0.5f, 0.5f); 

    sf::Sprite exitButton(exitTexture);
    exitButton.setPosition(500.f, 350.f);
    exitButton.setScale(0.5f, 0.5f);


    sf::Sprite nextLevelButton(nextLevelTexture);
    nextLevelButton.setPosition(250.f, 190.f);
    nextLevelButton.setScale(0.5f, 0.5f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // CHECK: Código muy anidado, máximo 3 anidaciones
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (nextLevelButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    increaseLevel();
                    window.close();
                    startNewLevel();  

                }


                if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    window.close();
                    handleLevels(currentLevel);
                    startNewLevel();
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
        window.draw(nextLevelButton);
        window.display();
    }
}


void game::showGameOverdWindow()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FinalWindow", sf::Style::Close);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/GameOverBackround.png")) {
        std::cout << "Error: no se pudo cargar la imagen\n";
    }

    sf::Sprite background(backgroundTexture);

    background.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );

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
        window.draw(restartButton);
        window.draw(exitButton);
        window.display();
    }
}


void game::handleLevels(int level)
{
    currentLevel = level;

    if (level == 1) {
        targetGemColor = 0;   
        targetGemCount = 15;
        currentCount = 0;
        cout << "Nivel 1: elimina 15 gemas rojas\n";
    }
    if (level == 2) {
        targetGemColor = 1;   
        targetGemCount = 25;
        currentCount = 0;
        cout << "Nivel 2: elimina 25 gemas verdes\n";
    }
    if (level == 3) {
        targetGemColor = 2;  
        targetGemCount = 30;
        currentCount = 0;
        cout << "Nivel 3: elimina 30 gemas azules\n";
    }
}

void game::increaseLevel() {
    int nextLevel = currentLevel + 1;

    if (nextLevel > 3) {
        cout << "¡Felicidades! Completaste todos los niveles\n";
        showFinalLevelWindow();
    }
    else {
        handleLevels(nextLevel);
        board.fillBoard();
        processMatches();
        board.createGemSprites();
    }
}


void game::verifyEndGame()
{
    if (movements <= 0)
    {
        if (currentCount >= targetGemCount) {

            showFinalLevelWindow();
        }
        else {
            showGameOverdWindow();
        }
    }
}

void game::startNewLevel()
{
    currentCount = 0;
    points = 0;
    movements = 20;

    isFirstClick = true;
    showBoardWindow();

    handleLevels(currentLevel);
}