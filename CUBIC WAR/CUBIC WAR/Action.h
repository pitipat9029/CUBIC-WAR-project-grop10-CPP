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

	int idPlayerNow = 0;
	std::vector<Player*> vPlayers;
	
	std::vector<sf::Sprite> grids;

	sf::Vector2f* pMousePosView;
	sf::Vector2i currentMousePos;
	bool isMousePress = false;

	bool isWait = false;
	bool isMoveMode = false;
	bool isCreatdMode = false;

	Grid* pGridMoveStart = 0;
	Grid* pGridPointed = 0;

	Grid* CheckGridPointed();
	void CreateGridArea(int);

	void ClickEvents();
	void NextTurn();

	void HighlightGridPointed(sf::Color, sf::Color);
	void HighlightGridArea(sf::Color, sf::Color);
	void ShowGridHighlight();
	void RandomStartPosition();

	void RenderUnit();
	void Move();
	
public:
	Action(sf::RenderWindow*, sf::Vector2f*);
	~Action();

	void Render();
	void StartGame(int);
	void GameEnd();
};