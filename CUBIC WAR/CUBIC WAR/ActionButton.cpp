#include "ActionButton.h"

ActionButton::ActionButton(std::string type)
{
	this->typeAction = type;
	if (type == "Move") {
		
	}else if(type == "Build") {
		
	}else if (type == "B-M") {

	}else if (type == "B-C") {

	}else if (type == "B-D") {

	}
	
	shape.setRadius(10);
	shape.setOrigin(5, 5);
}

ActionButton::~ActionButton()
{
}

void ActionButton::SetPosition(sf::Vector2f Pos)
{
	this->shape.setPosition(Pos);
}

void ActionButton::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

float ActionButton::distanceFromMouse(sf::Vector2i MousePos)
{
	float x = float(pow(shape.getPosition().x - MousePos.x, 2));
	float y = float(pow(shape.getPosition().y - MousePos.y, 2));

	return sqrt(x + y);
}

bool ActionButton::isPointed(sf::Vector2i MousePos)
{
	if (this->shape.getGlobalBounds().contains(float(MousePos.x), float(MousePos.y))) return true;
	return false;
}

std::string ActionButton::GetActionCommand()
{
	return this->typeAction;
}
