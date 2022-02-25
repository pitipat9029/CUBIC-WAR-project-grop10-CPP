#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "MyButton.h"
#include "Action.h"

class UImanager
{
	sf::RenderWindow* pWindow;
	Action* gameAction;

	MyButton* pBtnStart;

	sf::Texture tbgStart;
	sf::Sprite bgStart;
	sf::Texture tbgWin;
	sf::Sprite bgWin;

	sf::RectangleShape returnMenubtn;
	sf::RectangleShape restartbtn;

	sf::Font font;
	sf::Text tPlayerWin;
	sf::Text tReturnMenubtn;
	sf::Text tRestartbtn;
	sf::Text tWin;

public:
	UImanager(sf::RenderWindow* pWindow, Action* gameAction);
	~UImanager();

	std::string RenderUI(std::string page);
};

