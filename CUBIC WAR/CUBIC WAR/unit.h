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
	
	std::string type = "";
	int hp;
	int maxhp;
	int price;
	int atk;
	int moveRadius;

	int idPlayer;

public:
	Unit(std::string, sf::Vector2f, int);
	~Unit();
	void Render(sf::RenderTarget* target);
	void SetSize(float, float);
	void Move(sf::Vector2f);
	bool isMyUnit(int);
	std::string GetType();
};


