#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Game
{
private:
	sf::VideoMode videoMode;
	sf::Event event;

	void initWindow();
	void pollEvents();

public:
	sf::RenderWindow* window;

	// Consturctor & Desturctor
	Game();
	~Game();

	const bool IsRuning() const;

	// Function
	void Update();
	void Render();
};

