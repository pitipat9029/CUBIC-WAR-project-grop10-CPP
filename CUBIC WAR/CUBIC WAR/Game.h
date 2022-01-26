#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"

#include "Building.h"
#include "Maptest.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::Event event;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;


	void initWindow();
	void initMap();

	void pollEvents();

	void initVariable();
	void initFont();
	void initText();

	void UpdateMousePosition();

	Building Building;
	Maptest *Map;


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
	void Render();

	void RenderGui(sf::RenderTarget* target);
};

