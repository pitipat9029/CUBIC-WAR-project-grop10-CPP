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

	void initWindow();
	void initVariable();
	void initPlayer(int);

	void pollEvents();

	void UpdateMousePosition();


public:
	sf::RenderWindow* window;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	Action* gameAction;
	Map* map;

	std::vector<Player> gamePlayers;

	// Consturctor & Desturctor
	Game();
	~Game();

	const bool IsRuning() const;

	// Function
	void Update();
	void Render();
};

