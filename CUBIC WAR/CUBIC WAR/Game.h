#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

#include "Action.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Clock clock1sec;
	sf::Time t1; 

	sf::RectangleShape button;
	sf::RectangleShape bar;


	Action* gameAction;

	int points;
	int time;

	int roll1, roll2;
	

	sf::Font font;
	sf::Text guiText;
	sf::Text timer;

	void initWindow();
	void initVariable();
	void initButton();
	void initBar();

	void pollEvents();
	void initFont();
	void initText();
	void initTimer();

	void UpdateMousePosition();


public:
	sf::RenderWindow* window;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Consturctor & Desturctor
	Game();
	~Game();

	const bool IsRuning() const;

	// Function
	void Update();
	void updateGui();
	void updateTime();
	void Render();

	void renderButton(sf::RenderTarget*);
};

