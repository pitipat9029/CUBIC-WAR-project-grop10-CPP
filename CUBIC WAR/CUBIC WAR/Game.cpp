#include "Game.h"

Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete window;
}

const bool Game::IsRuning() const
{
	return this->window->isOpen();
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
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

void Game::Update()
{
	this->pollEvents();
}

void Game::Render()
{
	this->window->clear();

	//Code draw things here

	this->window->display();
}
