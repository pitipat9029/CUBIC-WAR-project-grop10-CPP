#include "Building.h"

Building::Building()
{
	if (!texture.loadFromFile("Textures/Terrain/grass_05.png")) {
		std::cout << "Error!";
	}
}

Building::~Building()
{
}

void Building::Render(sf::RenderTarget *target)
{
	grid.setTexture(this->texture);
	target->draw(grid);
}

void Building::CreateBuilding(std::string type)
{
	this->isBuilding = true;
	this->typeBuilding = type;

	if(type == "B") {
		this->maxLifePoint = this->lifePoint = 50;
		this->damage = 0;
		this->imgPath = "medieval_largeCastle";
	}
	else if (type == "M") {
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		this->imgPath = "medieval_training";
	}
	else if (type == "A") {
		this->maxLifePoint = this->lifePoint = 45;
		this->damage = 0;
		this->imgPath = "medieval_tower";
	}
	else if (type == "C") {
		this->maxLifePoint = this->lifePoint = 35;
		this->damage = 0;
		this->imgPath = "medieval_canon";
	}

	if (!this->texture.loadFromFile("Textures/Building/" + this->imgPath + ".png")) {
		std::cout << "Error to load Textures/Building/" + this->imgPath + ".png" << std::endl;
	}
}


