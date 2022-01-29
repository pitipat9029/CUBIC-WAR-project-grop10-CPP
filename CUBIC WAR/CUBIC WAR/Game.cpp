#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initVariable();
	this->initFont();
	this->initText();

	this->initMap();
}

Game::~Game()
{
	delete window;
	delete map;
	delete building;
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
	this->map = new Maptest;
	this->building = new Building(this->map, this->window, this->map->gridInfos, &this->mousePosView);
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

void Game::initVariable()
{
	this->points = 0;

}

void Game::initFont()
{
	this->font.loadFromFile("Fonts/Minecraft.ttf");
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::Blue);
	this->guiText.setCharacterSize(32);
}

void Game::UpdateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::Update()
{
	this->pollEvents();
	this->player.update(this->window);
	this->updateGui();
	this->UpdateMousePosition();
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Points: " << this->points;
	this->guiText.setString(ss.str());
}
 
void Game::Render()
{

	this->window->clear();

	//Code draw things here
	this->player.render(this->window);
	this->map->Render(*this->window);
	this->building->Update(this->player.myBuildings);

	//Render gui
	//this->RenderGui(this->window);
	this->window->display();

}

void Game::RenderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}
