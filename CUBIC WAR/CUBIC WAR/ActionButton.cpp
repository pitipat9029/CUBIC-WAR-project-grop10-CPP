#include "ActionButton.h"
ActionButton::ActionButton(std::string type , int usePoint)
{
	this->typeAction = type;
	this->usePoint = usePoint;
	imgPath = "gun-target";
	if (type == "Move") {
		imgPath = "move-selection";
	}else if(type == "SelectBuild") {
		imgPath = "hammer";
	}else if (type == "B_M") {
		imgPath = "medieval_doorway";
	}else if (type == "B_C") {
		imgPath = "turret_small";
	}else if (type == "B_A") {
		imgPath = "tower";
	}else if (type == "SelectCreate") {
		imgPath = "add";
	}else if (type == "U_Soldier") {
		imgPath = "Soldier";
	}else if (type == "U_Archer") {
		imgPath = "Archer";
	}else if (type == "U_Artillery") {
		imgPath = "Artillery";
	}else if (type == "U_") {
		imgPath = "move-selection";
	}else if (type == "Attack") {
		imgPath = "gun-target";
	}

	if (!this->texture.loadFromFile("Textures/Button/" + this->imgPath + ".png")) {
		std::cout << "Error to load Textures/Button/" + this->imgPath + ".png" << std::endl;
	}
	
	float k;
	if (this->texture.getSize().y > this->texture.getSize().x) {
		k = (this->size - 5) / this->texture.getSize().y;
	}
	else {
		k = (this->size - 5) / this->texture.getSize().x;
	}
	img.scale(k, k);
	//img.setOrigin((this->texture.getSize().x * k) /4, (this->texture.getSize().y * k) /4);
	shape.setRadius(size/2);
	shape.setOrigin(size/4, size/4);
}

ActionButton::~ActionButton()
{
}


void ActionButton::SetPosition(sf::Vector2f Pos)
{
	this->img.setTexture(this->texture);
	this->shape.setPosition(Pos);
	this->img.setPosition(Pos.x - 2.5f, Pos.y - 2.5f);
}

void ActionButton::Render(sf::RenderTarget* target, int point)
{
	this->shape.setFillColor(sf::Color::White);
	target->draw(this->shape);
	target->draw(this->img);
	if (point < this->usePoint)
	{
		this->shape.setFillColor(sf::Color(0,0,0,180));
		target->draw(this->shape);
	}
}

float ActionButton::distanceFromMouse(sf::Vector2i MousePos)
{
	float x = float(pow(shape.getPosition().x - MousePos.x, 2));
	float y = float(pow(shape.getPosition().y - MousePos.y, 2));

	return sqrt(x + y);
}

bool ActionButton::isPointed(sf::Vector2i MousePos )
{
	if (this->shape.getGlobalBounds().contains(float(MousePos.x), float(MousePos.y))) return true;
	return false;
}

std::string ActionButton::GetActionCommand(int playerPoint)
{
	if (playerPoint >= this->usePoint)
	{
		return this->typeAction;
	}
	return "null";
}

int ActionButton::GetUsePoint()
{
	return this->usePoint;
}
