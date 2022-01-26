#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initMap();
}

Game::~Game()
{
	delete window;
	delete Map;
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
	this->window->setFramerateLimit(60);
}

void Game::initMap()
{
	this->Map = new Maptest;
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

	//Code draw things here
	this->Map->Render(*this->window);
	this->Building.Create(this->Map->gridInfos, this->mousePosView, *this->window);
	

	this->window->display();
}
