#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class ActionButton
{
private:
	float size = 30;
	std::string imgPath = "";
	sf::Texture texture;
	sf::Sprite img;

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
	int GetUsePoint();
};

