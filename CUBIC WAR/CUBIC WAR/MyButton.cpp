#include "MyButton.h"

void MyButton::Setup()
{

}

MyButton::MyButton(std::string massage, sf::Vector2f Pos)
{
	this->font.loadFromFile("Fonts/StayPixelRegular-EaOxl.ttf");
	

	this->shapeCenter.setSize(sf::Vector2f(100.f, 50.f));
	this->shapeCenter.setOrigin(100.f / 2, 50.f / 2);
	this->shapeCenter.setPosition(Pos);
	this->shapeCenter.setFillColor(sf::Color(245, 222, 179));
	this->shapeRight.setRadius(25.f);

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color(139, 69, 19));
	this->text.setCharacterSize(32);
	this->text.setString(massage);

	sf::FloatRect textRect = text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->text.setPosition(shapeCenter.getPosition());
	
}

void MyButton::Render(sf::RenderTarget* target)
{
	target->draw(this->shapeCenter);
	target->draw(this->text);
}

void MyButton::SetPosition(sf::Vector2f Pos)
{
	shapeCenter.setPosition(Pos);
}
