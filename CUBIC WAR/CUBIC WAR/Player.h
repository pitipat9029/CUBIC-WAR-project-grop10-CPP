#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Player
{
private:
	sf::Vector2i startposition;
	void randomporition();

public:
	Player(float x = 0.f,float y = 0.f);
	virtual ~Player();
};

