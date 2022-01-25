#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Maptest
{
private:
	struct gridInfo {
		std::string type;
		int buildingID = 0;
		int x = 0;
		int y = 0;
	};

	sf::RectangleShape grid;

	float gridSize;
	std::vector<gridInfo> gridInfos;
	std::vector<sf::RectangleShape> grids;

	void InitMap();

public:

	Maptest();
	~Maptest();

	void Render(sf::RenderTarget &);
};