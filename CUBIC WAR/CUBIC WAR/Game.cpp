#include "Game.h"

Game::Game()
{
	this->initWindow();
	this->initVariable();
	this->initFont();
	this->initText();
	this->initTimer();
	this->initButton();
	this->initBar();
	this->points = 0;
}

Game::~Game()
{
	delete gameAction;
	delete window;
}

const bool Game::IsRuning() const
{
	return this->window->isOpen();
}

// Setting window and main events

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 900;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initVariable()
{
	this->gameAction = new Action(this->window, &this->mousePosView);
	this->gameAction->StartGame(2);
}

void Game::initButton()
{
	this->button.setFillColor(sf::Color::Red);
	this->button.setSize(sf::Vector2f(50.f, 50.f));
	this->button.setPosition(850.f, 550.f);
}

void Game::initBar()
{
	sf::Color temp(196, 164, 132);
	this->bar.setFillColor(temp);
	this->bar.setSize(sf::Vector2f(900.f, 100.f));
	this->bar.setPosition(0.f,550.f);
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
			if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
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
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	this->guiText.setPosition(5.f, 550.f);
}

void Game::initTimer()
{
	this->timer.setFont(this->font);
	this ->timer.setFillColor(sf::Color::White);
	this->timer.setCharacterSize(32);
	this->timer.setPosition(200.f, 550.f);
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
	this->updateGui();
	this->updateTime();
}

void Game::updateGui()
{
	std::stringstream ss;

	ss << "Points: " << this->points;
	this->guiText.setString(ss.str());
}

void Game::updateTime()
{
	//Timer
	std::stringstream tt;

	t1 = clock1sec.getElapsedTime();
	time = (int)t1.asSeconds();
	if (time / 11 == 1)
	{
		clock1sec.restart();
	}
	tt << "Timer: " << this->time;
	this->timer.setString(tt.str());
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
