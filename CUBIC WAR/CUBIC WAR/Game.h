#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Building.h"
#include "Maptest.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::Event event;

	void initWindow();
	void initMap();

	void pollEvents();
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
	void Render();
};

