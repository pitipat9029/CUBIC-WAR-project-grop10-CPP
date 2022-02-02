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
	Map* map;
	sf::RenderWindow* window;
	sf::Vector2f* mousePosView;

	struct sBuildingInfo {
		std::string type;
		int maxLifePoint = 0, maxDamage = 0;
		sf::RectangleShape object;
	};

	bool isCreatdMode;

public:
	std::vector<Map::gridInfo>& gridInfos;
	std::vector<Player>& gamePlayers;

	//std::vector<sPlayerBuilding> playerBuildings;

	Action(Map*, sf::RenderWindow*, std::vector<Map::gridInfo>&, std::vector<Player>&, sf::Vector2f*);
	~Action();

	void Update();
	void Render();
	void AddBuilding(int, float, float);
	void Create();
};