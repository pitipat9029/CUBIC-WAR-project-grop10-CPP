#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initPlayer(2);
	this->initVariable();
	this->initFont();
	this->initText();
	this->initButton();
	this->points = 0;
}

Game::~Game()
{
	delete window;
	delete map;
	delete gameAction;
}

const bool Game::IsRuning() const
{
	return this->window->isOpen();
}

// Seting Game start

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 900;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initVariable()
{
	this->map = new Map;
	this->gameAction = new Action(this->map, this->window, this->map->vGrids, this->gamePlayers, &this->mousePosView);
}

void Game::initButton()
{
	this->button.setFillColor(sf::Color::Red);
	this->button.setSize(sf::Vector2f(50.f, 50.f));
	this->button.setPosition(0.f, 0.f);
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
		if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			button.setFillColor(sf::Color::Blue);
		}
		else
		{
			button.setFillColor(sf::Color::Red);
		}
		
		//button press
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			/*if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
			{
				std::cout << "Start Your turn\n";
				roll1 = (rand() % 6) + 1;
				roll2 = (rand() % 6) + 1;
				

				points = roll1 + roll2;
				std::cout << "dice1 = " << roll1 << "\n";
				std::cout << "dice2 = " << roll2 << "\n";
				std::cout << "Your total points is " << points << "\n";

				if (roll1 == roll2)
				{
					std::cout << "U can roll again! \n";
				}
			}*/
			
		}

	}
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
	this->UpdateMousePosition();

	//Timer
	/*t1 = clock1sec.getElapsedTime();
	int num = (int)t1.asSeconds();
	printf("%d\n", num);
	if (num / 5 == 1)
	{
		clock1sec.restart();
	}*/
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

	//--------------------------

	//Code draw things here
	//this->player.render(this->window);
	this->map->Render(this->window);
	this->gameAction->Update();
	

	//--------------------------

	//Render gui
	window->draw(button);
	//this->RenderGui(this->window);
	this->window->display();
}

void Game::renderButton(sf::RenderTarget* target)
{
	target->draw(this->button);
}
