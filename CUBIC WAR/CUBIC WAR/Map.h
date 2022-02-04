#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Building.h"

class Map
{
private:
	float gridSize;
	void InitMap();

public:
	std::vector<Building> grids;

	Map();
	~Map();

	void Render(sf::RenderTarget *);
};