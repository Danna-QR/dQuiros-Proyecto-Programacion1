#pragma once
#include "board.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
using namespace std;


class game
{
private:
	board board;

	bool isFirstClick = true;// CHECK: debe seguir el estandar de nombres para variables booleanas
	bool isMousePressed = false; // CHECK: debe seguir el estandar de nombres para variables booleanas
	int rowFirstClick, colFirstClick;
	int rowSecondClick;
	int colSecondClick;
	int movements = 20;
	int points = 0;

	sf::Font font;
	sf::Text movementText;
	sf::Text pointsText;

	int currentLevel;     
	int targetGemColor; 
	int targetGemCount;      
	int currentCount;     

public:
	game();
	void showPrincipalWindow();
	void showBoardWindow();
	void  decreaseMovements(int& movements);
	void  sumPoints(int& points);
	void handleMove();
	void processMatches();
	void handleMouseClick(sf::RenderWindow& window);
	void showFinalLevelWindow();

	void showGameOverdWindow();
	void handleLevels(int level);
	void increaseLevel();
	void verifyEndGame();
	void startNewLevel();
};
