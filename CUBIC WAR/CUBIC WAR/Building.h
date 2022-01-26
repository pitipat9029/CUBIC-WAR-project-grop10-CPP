#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "Maptest.h"

class Building
{
private:
	int Type;
	double LifePoint, Damage;
	int Area[5][3][3] = { 
		{{1,1,1},{1,1,1},{1,1,1}},
		{{0,0,0},{0,1,1},{0,0,0}},
		{{0,0,0},{0,1,1},{0,1,1}},
		{{0,0,0},{0,0,0},{0,0,0}},
		{{0,0,0},{0,0,0},{0,0,0}}
	};


public:
	
	Building();
	~Building();

	void Render();
	void Create(std::vector<Maptest::gridInfo>, sf::Vector2f, sf::RenderTarget&);
	void Attack();
};

