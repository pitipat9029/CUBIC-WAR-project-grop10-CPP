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
	int* pIdPlayerNow;
	sf::RenderWindow* pWindow;
	sf::Vector2f gridSize;
	int maxColumn, maxRow;

	sf::Vector2i* currentMousePos;
	Grid* pPointedGrid;
	
	void InitMap();

public:
	Map(sf::RenderWindow* pWindow, sf::Vector2i*, int*);
	~Map();

	std::vector<std::vector<Grid>> vGrids;
	std::vector<Unit *> vUnits;

	void RenderMap();
	void RenderUnits();
	void UpdatePlayerVision(Grid*, int, int);

	Grid* UpdatePointedGrid();
	void ShowGridHighlight(std::string mode);
	void SetGridAllEnable(bool);
	void SetGridEdgeDisable();

	void CreateGridArea(Grid* pGridCenter, int radius);
	void HighlightGridArea(sf::Color cFill, sf::Color cOutline);
	void HighlightGridPointed(sf::Color cFill, sf::Color cOutline);
};