#pragma once
#include <SFML/Graphics.hpp>

class ActionButton
{
private:
	std::string typeAction = "";
	sf::CircleShape shape;

	void Setup();
public:
	ActionButton(std::string);
	void SetPosition(sf::Vector2f);
	void Render(sf::RenderTarget* target);
};

