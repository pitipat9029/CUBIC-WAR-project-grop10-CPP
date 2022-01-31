#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Building
{
private:
	std::string type; //[0 = base, 1 = military, 2 = canon, 3 = archery, 4 wall]
	int id = 0;
	int maxLifePoint = 0, maxDamage = 0;
	int lifePoint = 0, damage = 0;
	
public:
	sf::RectangleShape object;

	Building();
	~Building();
};

