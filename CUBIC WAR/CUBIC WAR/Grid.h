#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "Unit.h"

class Grid
{
private:
	int row = 0, column = 0;
	sf::Vector2f size;
	sf::Vector2f centerPos;
	bool enabled = true;
	void Setup();

	std::string imgPath = "";
	sf::Texture texture;
	sf::Sprite shape;
	
	std::string typeBuilding = "";
	int maxLifePoint = 0, lifePoint = 0;
	int damage = 0;

	Unit* pUnit = 0;
	
public:
	bool isBuilding = false;
	bool isUnit = false;

	Grid(int, int, sf::Vector2f);
	~Grid();

	void Render(sf::RenderTarget*);
	void CreateBuilding(std::string type);

	void AddUnit(std::string type, std::vector<Unit*>&);
	void AddUnit(Unit*);
	Unit* GetUnit();
	void ClearUnit();

	void SetEnabled(bool);

	bool isHovered(sf::Vector2i);
	bool isEnabled();
	float distanceFromMouse(sf::Vector2i);
	sf::Vector2f GetPosition();
	sf::Vector2i GetRC();
	
};

