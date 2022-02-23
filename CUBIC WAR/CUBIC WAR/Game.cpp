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
	this->initSound();
	this->points = 0;
	this->playerturn = 1;
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
	this->gameAction = new Action(this->window);
}

void Game::initButton()
{
	sf::Color temp(196, 164, 132);
	this->startbtn.setFillColor(temp);
	this->startbtn.setSize(sf::Vector2f(220.f, 72.f));
	this->startbtn.setPosition(350.f, 350.f);

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(32);
	this->text.setPosition(355.f, 360.f);
	this->text.setString("START GAME");
}

void Game::initBar()
{
	sf::Color temp(196, 164, 132);
	this->bar.setFillColor(temp);
	this->bar.setSize(sf::Vector2f(900.f, 100.f));
	this->bar.setPosition(0.f,550.f);
}

void Game::initSound()
{
	soundBuffer.loadFromFile("Audio/clickSound.wav");
	
	sound.setBuffer(soundBuffer);
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
			if (this->event.key.code == sf::Keyboard::P) {
				sound.play();
				std::cout << "P push";
			}
			break;
		}
		if (startbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
		{
			sf::Color temp(150, 1200, 100);
			startbtn.setFillColor(temp);
		}
		else
		{
			sf::Color temp(196, 164, 132);
			startbtn.setFillColor(temp);
		}
		//start game click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (startbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
			{
				std::cout << "startbtn is clicked";
				this->gameAction->StartGame(2);
				startbtn.setPosition(910.f,610.f);
				guiText.setPosition(910.f, 610.f);
				text.setPosition(910.f, 619.f);
			}
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
	this->guiText.setCharacterSize(75);
	this->guiText.setPosition(250.f, 230.f);
	guiText.setString("CUBIC WAR");
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
	this->updateTurnText();
	this->updateTime();
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

void Game::updateTurnText()
{
	std::stringstream textt;

	textt << "Player " << this->playerturn << " turn";
	this->turntext.setString(textt.str());
}
 
void Game::Render()
{
	this->window->clear();

	//--------------------------
	window->draw(guiText);
	//Code draw things here
	//this->player.render(this->window);
	window->draw(startbtn);
	window->draw(text);
	
	if (this->gameAction->isGamePlaying == true) {
		this->gameAction->Render();
	}
	
	//--------------------------

	//Render gui
	//window->draw(bar);
	//window->draw(timer);
	//this->RenderGui(this->window);
	this->window->display();


}

void Game::renderButton(sf::RenderTarget* target)
{
	target->draw(this->startbtn);
}
