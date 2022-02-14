#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "Unit.h"
#include "ActionButton.h"

class Grid
{
private:
	bool enabled = true;

	// Figure -----
	int row = 0, column = 0;
	sf::Vector2f size;
	sf::Vector2f centerPos;
	std::string imgPath = "";
	sf::Texture texture;
	sf::Sprite shape;
	
	void Setup();

	bool idPlayersVision[2] = {};
	int idPlayerHere = -1;
	
	// Building ----
	std::string typeBuilding = "";
	int maxLifePoint = 0, lifePoint = 0;
	int damage = 0;
	std::string* pListMenu = 0;

	// Unit -------
	Unit* pUnit = 0;
	
public:
	bool isBuilding = false;
	bool isUnit = false;
	std::vector<ActionButton*> vActionButton;

	Grid(int, int, sf::Vector2f);
	~Grid();

	void setActionButtons(int, std::string[]);

	void RenderGrid(sf::RenderTarget*);
	void RenderUnit(sf::RenderTarget*);
	Grid* CreateBuilding(std::string type, int);
	void SetEnabled(bool);

	bool isPointed(sf::Vector2i);
	bool isEnabled();
	float distanceFromMouse(sf::Vector2i);
	sf::Vector2f GetPosition();
	sf::Vector2i GetRC();
	sf::Vector2f GetCenterPoint();
	void UpdatePlayerVision(int idPlayer);
	bool GetPlayerVision(int idPlayer);
	
	// Unit
	Grid* AddUnit(std::string type, std::vector<Unit*>&, int);
	Grid* AddUnit(Unit*);
	void ClearUnit();
	Unit* GetUnit();
};

