#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Unit
{
private:
	sf::Sprite shape;
	std::string imgPath = "";
	sf::Texture texture;
	sf::Vector2f size;
	int points;

	std::string type = "";
	int hp;
	int maxhp;

	int atk;
	int moveRadius;

public:
	Unit(std::string, sf::Vector2f);
	~Unit();
	void Render(sf::RenderTarget* target);
	void SetSize(float, float);
	void Move(sf::Vector2f);
};


