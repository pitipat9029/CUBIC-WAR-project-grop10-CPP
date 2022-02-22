#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Grid.h"

class Player
{
private:
	sf::Vector2i startposition;
	void randomporition();
	

public:


	sf::Vector2f whoAttack;
	std::vector<Grid* > whereAttack;

	int point = 0;
	Player(float x = 0.f,float y = 0.f);
	virtual ~Player();
};

