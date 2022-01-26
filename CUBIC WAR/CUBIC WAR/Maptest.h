#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Maptest
{
private:
	sf::RectangleShape grid;

	float gridSize;
	void InitMap();

public:

	struct gridInfo {
		int id = 0;
		std::string type;
		int buildingID = 0;
		int x = 0;
		int y = 0;
	};

	std::vector<gridInfo> gridInfos;
	std::vector<sf::RectangleShape> grids;

	Maptest();
	~Maptest();

	void Render(sf::RenderTarget &);
};