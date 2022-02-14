#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Map.h"
#include "Player.h"
#include "Grid.h"
#include "ActionButton.h"

class Action
{
private:
	void Update();

	sf::RenderWindow* pWindow;

	Map* pMap = 0;

	int countTurn = 0;
	bool isWait = true;
	int idPlayerNow = 0;
	std::vector<Player*> vPlayers;
	
	sf::Vector2i currentMousePos;
	bool isMousePress = false;

	bool isMenuOpen = false;
	std::string gMode = "Normal";
	
	Grid* pGridSelected = 0;
	Grid* pGridPointed = 0;

	void SetToNormalMode();
	void ClickEvents();
	void NextTurn();
	void RandomStartPosition();

	void Move();

	void RenderMenu();
	
public:
	Action(sf::RenderWindow*);
	~Action();

	void Render();
	void StartGame(int);
	void GameEnd();
};