#include "Game.h"

const bool Game::IsRuning() const
{
	return this->window->isOpen();
}

// Seting Game start

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initVariable()
{
	this->map = new Map;
	this->gameAction = new Action(this->map, this->window, this->map->gridInfos, this->gamePlayers, &this->mousePosView);
}

void Game::initPlayer(int numbers)
{
	Player player;
	for (int i = 0; i < numbers; i++) {
		gamePlayers.push_back(player);
	}
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event)) {

		switch (this->event.type)  
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
			break;
		}

	}
}

void Game::UpdateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::Update()
{
	this->pollEvents();
	this->UpdateMousePosition();
}
 
void Game::Render()
{
	this->window->clear();

	//--------------------------

	this->map->Render(*this->window);
	this->gameAction->Update();

	//--------------------------

	this->window->display();
}

Game::Game()
{
	this->initWindow();
	this->initPlayer(2);
	this->initVariable();
}

Game::~Game()
{
	delete window;
	delete map;
	delete gameAction;
}
