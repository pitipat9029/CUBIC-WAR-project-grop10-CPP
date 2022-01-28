#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu(float width, float height)
{
	sf::Font font;
	if (!font.loadFromFile("MILD.ttf")) 
	{
		cout << "can not find font ";
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("START");
	menu[0].setPosition(sf::Vector2f( width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("setting");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));


}
Menu::~Menu()
{


}

void Menu::draw(sf::RenderWindow& window) 
{
	for (int i = 0; i < MAX_ITEMS; i++) 
	{
		window.draw(menu[i]);
	}
}




