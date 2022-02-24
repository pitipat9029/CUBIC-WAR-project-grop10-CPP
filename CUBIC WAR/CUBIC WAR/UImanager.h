#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "MyButton.h"

class UImanager
{
	sf::RenderWindow* pWindow;

	MyButton* pBtnStart;

	sf::Texture tbgStart;
	sf::Sprite bgStart;

public:
	UImanager(sf::RenderWindow* pWindow);
	~UImanager();

	void RenderUI(std::string page);
};

