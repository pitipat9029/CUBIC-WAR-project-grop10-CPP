#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>

#include "Action.h"
#include "UImanager.h"

class Game
{
private:
	std::string pageNow;

	sf::VideoMode videoMode;
	sf::Event event;

	sf::Clock clock1sec;
	sf::Time t1; 

	sf::RectangleShape startbtn;
	sf::RectangleShape bar;

	//sound
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::SoundBuffer soundBufferclick;
	sf::Sound clicksound;

	Action* gameAction;
	UImanager* gameUImanager;
	ActionButton* actionButton;

	int playerturn;
	int points;
	int time;

	int roll1, roll2;

	sf::Font font;
	sf::Text guiText;
	sf::Text timer;
	sf::Text turntext;
	sf::Text text;

	void initWindow();
	void initVariable();
	void initButton();
	void initBar();
	//sound
	void initSound();

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
	void updateTime();
	void updateTurnText();
	void Render();

	void renderButton(sf::RenderTarget*);
};

