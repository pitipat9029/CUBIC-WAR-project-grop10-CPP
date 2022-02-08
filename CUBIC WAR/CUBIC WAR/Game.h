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

	Player player;
	std::vector<Player> gamePlayers;
	Action* gameAction;

	int points;

	int roll1, roll2;
	

	sf::Font font;
	sf::Text guiText;

	void initWindow();
	void initVariable();
	void initPlayer(int);
	void initButton();

	void pollEvents();
	void initFont();
	void initText();

	void UpdateMousePosition();


public:
	sf::RenderWindow* window;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	Map* map;

	// Consturctor & Desturctor
	Game();
	~Game();

	const bool IsRuning() const;

	// Function
	void Update();
	void updateGui();
	void Render();

	void RenderGui(sf::RenderTarget* target);
	void renderButton(sf::RenderTarget*);
};

