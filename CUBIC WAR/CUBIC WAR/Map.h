#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Map
{
private:
	float gridSize;
	void InitMap();

public:

	struct gridInfo {
		int id = 0;
		std::string type;
		int buildingID = 0;
		float x = 0, y = 0;
		int row = 0, column = 0;
		sf::Sprite grid;
	};

	std::vector<gridInfo> gridInfos;

	Map();
	~Map();

	void Render(sf::RenderTarget &);
};