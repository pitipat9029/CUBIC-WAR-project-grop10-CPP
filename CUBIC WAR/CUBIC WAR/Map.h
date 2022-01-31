#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Map
{
private:
	sf::Sprite grid;

	float gridSize;
	void InitMap();

public:

	struct gridInfo {
		int id = 0;
		std::string type;
		int buildingID = 0;
		float x = 0;
		float y = 0;
	};

	std::vector<gridInfo> gridInfos;
	std::vector<sf::Sprite> grids;

	Map();
	~Map();

	void Render(sf::RenderTarget &);
};