#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Unit
{
private:
	std::string type = "";
	int hp;
	int maxhp;
	int atk;
	int direction;
	int points;

public:
	Unit(std::string);
	~Unit();
};


