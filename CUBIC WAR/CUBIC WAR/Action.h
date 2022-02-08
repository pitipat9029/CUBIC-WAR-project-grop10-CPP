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
	Map* pMap;
	sf::RenderWindow* pWindow;
	sf::Vector2f* pMousePosView;
	Grid* pGridPointed = 0;
	std::vector<sf::Sprite> grids;
	sf::Vector2i currentMousePos;

	bool isCreatdMode;
	bool isMousePress = false;

	Grid* pGridMoveStart = 0;

	Grid* CheckGridPointed();
	void HighlightGrid();

	void HighlightMove(int);

public:
	std::vector<std::vector<Grid>>& gridInfos;
	std::vector<Player>& gamePlayers;

	Action(Map*, sf::RenderWindow*, std::vector<std::vector<Grid>>&, std::vector<Player>&, sf::Vector2f*);
	~Action();

	void Update();
};