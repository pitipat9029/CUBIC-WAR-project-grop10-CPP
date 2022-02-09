#include "Unit.h"

Unit::Unit(std::string type, sf::Vector2f centerPos)
{
	this->type = type;
	if (this->type == "Engineer") {
		this->imgPath = "Engineer";
	}
	else if (this->type == "Soldier") {
		this->imgPath = "Soldier";
	}
	else if (this->type == "Archer") {
		this->imgPath = "Archer";
	}
	else if (this->type == "Artillery") {
		this->imgPath = "Artillery";
	}

	if (!this->texture.loadFromFile("Textures/Unit/" + this->imgPath + ".png")) {
		std::cout << "Error to load Textures/Unit/" + this->imgPath + ".png" << std::endl;
	}

	this->shape.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	this->shape.setPosition(centerPos);
	this->SetSize(60.f, 70.f);
}

Unit::~Unit()
{
	std::cout << "Unit was delete." << std::endl;
}

void Unit::Render(sf::RenderTarget* target)
{
	this->shape.setTexture(this->texture);
	target->draw(this->shape);
}

void Unit::SetSize(float x, float y)
{
	this->shape.scale(x / this->texture.getSize().x, y / this->texture.getSize().y);
}

void Unit::Move(sf::Vector2f centerPos)
{
	this->shape.setPosition(centerPos);
	std::cout << this->shape.getPosition().x;
}


