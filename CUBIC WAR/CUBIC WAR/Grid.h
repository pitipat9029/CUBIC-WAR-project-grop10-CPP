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

	bool isBuilding = false;
	std::string typeBuilding = "";
	int maxLifePoint = 0, lifePoint = 0;
	int damage = 0;

	bool isUnit = false;
	Unit* pUnit = 0;
	
public:
	Grid(int, int, sf::Vector2f);
	~Grid();

	void Render(sf::RenderTarget*);
	void CreateBuilding(std::string type);
	bool isHovered(sf::Vector2i);
	float distanceFromMouse(sf::Vector2i);
	void SetEnabled(bool);
	bool isEnabled();
	sf::Vector2f GetPosition();
	
};

