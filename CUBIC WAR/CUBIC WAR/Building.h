#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Maptest.h"

class Building
{
private:
	Maptest* map;
	sf::RenderTarget* window;
	sf::Vector2f* mousePosView;

	bool isCreatdMode;
	int Area[5][3][3] = { 
		{{1,1,1},{1,1,1},{1,1,1}},
		{{0,0,0},{0,1,1},{0,0,0}},
		{{0,0,0},{0,1,1},{0,1,1}},
		{{0,0,0},{0,0,0},{0,0,0}},
		{{0,0,0},{0,0,0},{0,0,0}}
	};
	
public:
	struct sBuildingInfo {
		int id = 0;
		std::string type;
		int maxLifePoint = 0, maxDamage = 0;
		sf::RectangleShape object;
	};

	struct sPlayerBuilding {
		int id = 0;
		std::string type; //[0 = base, 1 = military, 2 = canon, 3 = archery, 4 wall]
		int lifePoint = 0, damage = 0;
		sf::RectangleShape object;
	};

	std::vector<Maptest::gridInfo>& gridInfos;
	
	//std::vector<sPlayerBuilding> playerBuildings;

	Building(Maptest*, sf::RenderTarget*, std::vector<Maptest::gridInfo>&, sf::Vector2f*);
	~Building();

	void Update(std::vector<sPlayerBuilding>&);
	void Render(std::vector<sPlayerBuilding>&);
	void Create(std::vector<Maptest::gridInfo>, std::vector<sPlayerBuilding>&);
};

