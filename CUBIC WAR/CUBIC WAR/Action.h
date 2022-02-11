#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Map.h"
#include "Player.h"
#include "Grid.h"

class Action
{
private:
	void Update();

	sf::RenderWindow* pWindow;

	Map* pMap = 0;

	int countTurn = 0;
	bool isWait = true;
	std::vector<Player*> vPlayers;
	int idPlayerNow = 0;

	sf::Vector2i currentMousePos;
	bool isMousePress = false;

	std::string gMode = "Normal";
	void SetToNormalMode();

	Grid* pGridMoveStart = 0;
	Grid* pGridPointed = 0;

	void ClickEvents();
	void NextTurn();
	void RandomStartPosition();

	void Move();
	
public:
	Action(sf::RenderWindow*);
	~Action();

	void Render();
	void StartGame(int);
	void GameEnd();
};