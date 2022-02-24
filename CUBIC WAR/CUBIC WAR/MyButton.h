#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MyButton
{
private:
	sf::Text text;
	sf::Font font;

	sf::RectangleShape shapeCenter;
	sf::CircleShape shapeRight;
	sf::CircleShape shapeLeft;

	void Setup();

public:
	MyButton(std::string massage, sf::Vector2f Pos);
	void Render(sf::RenderTarget* target);
	void SetPosition(sf::Vector2f);
};

