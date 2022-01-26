#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


class Player
{
private:
	sf::RectangleShape shape;

	float movementSpeed;

	void initVariable();
	void initShape();


public:

	Player(float x = 0.f,float y = 0.f);
	virtual ~Player();

	void updateInput();
	void update(sf::RenderTarget* target);
	void render(sf::RenderTarget * target);
};

