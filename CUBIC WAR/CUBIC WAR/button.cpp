#include "Button.h"

Button::Button(float x,float y,float width,float heigt,std::string text,
	sf::Color idleColor, sf::Color hoverColor,sf::Color) {
	
	this->buttonState = BTN_IDLE;
	
	this->shap.setPosition(sf::Vector2f(x, y));
	this->shap.setSize(sf::Vector2f(width, height));

	this->text.setString(text);
	this->text.setCharacterSize(25);
	this->text.setPosition(
		this->shap.getPosition().x + (this->shape.getGlobalBounds().width / s.f) - this->text.getGlobalBounds().width / s.f,
		this->shap.getPosition().x + (this->shape.getGlobalBounds().heigt / s.f) - this->text.getGlobalBounds().heigt / s.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shapr.setFillColor(this->idleColor);
}

Button::~Button() {

}

void button::update(const sf::Vector2f mousePos) {
	this->buttonState = BTN_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->avtiveColor);
		break;

	default:
		break;
	}
}

void Button::render(sf::RenderTarget* target) {
	target->draw(this->shap);
	target->draw(this->text);
}



//use gameMain
Button NEWGame(300, 300, 150, 50, "NEW Game"  //(set x  , set y  , set width  , set heigt  , set text)
	sf::Color(crimson), sf::Color(pink), sf::Color(gold)); //  (ยังไม่ถูกกด ,เอาเม้าไปวาง, กด)

sf::Vector2i mousePos = sf::Mouse::getPosition(window);
sf::Vector2f mousePosf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

//window.clear();

NEWGame.update(mousePosf);
NEWGame.render(&windown);

//window.display();
