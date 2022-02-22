#pragma once
#include <SFML/Graphics.hpp>

class ActionButton
{
private:
	std::string typeAction = "";
	sf::CircleShape shape;
	int usePoint;


public:
	ActionButton(std::string,int);
	~ActionButton();
	void SetPosition(sf::Vector2f);
	void Render(sf::RenderTarget* target , int);

	float distanceFromMouse(sf::Vector2i MousePos);
	bool isPointed(sf::Vector2i MousePos);
	std::string GetActionCommand(int);
};

