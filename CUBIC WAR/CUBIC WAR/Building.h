#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Building
{
private:
	int type; //[0 = base, 1 = military, 2 = canon, 3 = archery, 4 wall]
	int id = 0;
	int maxLifePoint = 0, lifePoint = 0;
	int damage = 0;
	
public:
	sf::RectangleShape object;

	Building(int);
	~Building();
};

