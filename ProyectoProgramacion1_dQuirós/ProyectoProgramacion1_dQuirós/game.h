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

	bool firstClick = true;
	bool mousePressed = false;
	int rowFirstClick, colFirstClick;
	int rowSecondClick;
	int colSecondClick;
	int movements = 20;

public:
	game();
	void showPrincipalWindow();
	void showBoardWindow();
	void  decreaseMovements(int& movements);
	void handleMouseClick(sf::RenderWindow& window);
};
