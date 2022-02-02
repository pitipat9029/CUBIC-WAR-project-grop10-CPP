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

	sf::RectangleShape button;

	Player player;

	int points;

	int roll1, roll2;
	

	sf::Font font;
	sf::Text guiText;

	void initWindow();
	void initMap();

	void pollEvents();

	void initButton();

	void initVariable();
	void initFont();
	void initText();

	void UpdateMousePosition();


public:
	sf::RenderWindow* window;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	std::vector<Player> players;

	Building* building;
	Maptest* map;

	// Consturctor & Desturctor
	Game();
	~Game();

	const bool IsRuning() const;

	// Function
	void Update();
	void updateGui();
	void updateButton();
	void Render();

	void renderButton(sf::RenderTarget* target);
	void RenderGui(sf::RenderTarget* target);
};

