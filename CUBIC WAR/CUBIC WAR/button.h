#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

enum button_states { BTN_IDLE =0,BTN_HOVER,BTN_ACTIVE};

class Button :
{
privste:
    shot unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height, std::string text,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    ~Button();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};