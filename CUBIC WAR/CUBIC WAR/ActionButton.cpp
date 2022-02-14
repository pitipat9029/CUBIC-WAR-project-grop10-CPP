#include "ActionButton.h"

ActionButton::ActionButton(std::string type)
{
	if (type == "Move") {
		this->typeAction = "Move";
	}else if(type == "Build") {
		this->typeAction = "Build";
	}
	shape.setRadius(10);
	shape.setOrigin(5, 5);
}

void ActionButton::SetPosition(sf::Vector2f Pos)
{
	this->shape.setPosition(Pos);
}

void ActionButton::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
