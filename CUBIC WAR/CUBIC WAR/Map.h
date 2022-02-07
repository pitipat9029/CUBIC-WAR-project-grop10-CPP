#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Unit.h"

class Map
{
private:
	sf::Vector2f gridSize;
	int maxColumn, maxRow;
	void InitMap();

public:
	Map();
	~Map();

	std::vector<Grid> vGrids;
	std::vector<Unit> vUnits;

	void Render(sf::RenderTarget *);
};