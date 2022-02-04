#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Map.h"
#include "Player.h"
#include "Building.h"

class Action
{
private:
	Map* pMap;
	sf::RenderWindow* pWindow;
	sf::Vector2f* pMousePosView;
	std::vector<sf::Sprite> grids;

	bool isCreatdMode;
	bool isMousePress = false;

public:
	std::vector<Building>& gridInfos;
	std::vector<Player>& gamePlayers;

	//std::vector<sPlayerBuilding> playerBuildings;

	Action(Map*, sf::RenderWindow*, std::vector<Building>&, std::vector<Player>&, sf::Vector2f*);
	~Action();

	void Update();
	void MousePointer();
};