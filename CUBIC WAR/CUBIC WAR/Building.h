#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Building
{
private:
	bool isBuilding = false;
	std::string typeBuilding = "";
	int maxLifePoint = 0, lifePoint = 0;
	int damage = 0;

	std::string imgPath = "medieval_training";
	sf::Texture texture;
	
public:
	sf::Sprite grid;

	int id = 0;
	float xPos = 0, yPos = 0;
	int row = 0, column = 0;

	Building();
	~Building();

	void Render(sf::RenderTarget*);
	void CreateBuilding(std::string type);
};

