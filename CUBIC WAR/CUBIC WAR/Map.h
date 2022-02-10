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
	sf::RenderWindow* pWindow;
	sf::Vector2f gridSize;
	int maxColumn, maxRow;
	void InitMap();

public:
	Map(sf::RenderWindow* pWindow);
	~Map();

	std::vector<std::vector<Grid>> vGrids;
	std::vector<Unit *> vUnits;

	void Render(sf::RenderTarget *, int idPlayer);
	void UpdatePlayerVision(Grid*, int, int);

	void ShowGridHighlight(Grid* pGridPointed, std::string mode);
	void SetGridAllEnable(bool);
	void SetGridEdgeDisable();

	void CreateGridArea(Grid* pGridCenter, int radius);
	void HighlightGridArea(sf::Color cFill, sf::Color cOutline);
	void HighlightGridPointed(Grid* pGridPointed, sf::Color cFill, sf::Color cOutline);
};