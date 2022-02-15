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
	this->gameAction->StartGame(2);
}

void Game::initButton()
{
	this->button1.setFillColor(sf::Color::Red);
	this->button1.setSize(sf::Vector2f(100.f, 50.f));
	this->button1.setPosition(800.f, 550.f);

	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(18);
	this->text.setPosition(680.f, 567.f);
	this->text.setString("-> Click to Start ur turn");
}

void Game::initBar()
{
	sf::Color temp(196, 164, 132);
	this->bar.setFillColor(temp);
	this->bar.setSize(sf::Vector2f(900.f, 100.f));
	this->bar.setPosition(0.f,550.f);
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

void Game::initFont()
{
	this->font.loadFromFile("Fonts/Minecraft.ttf");
}

void Game::initTurnText()
{
	this->turntext.setFont(this->font);
	this->turntext.setFillColor(sf::Color::White);
	this->turntext.setCharacterSize(32);
	this->turntext.setPosition(400.f, 280.f);
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
	this->updateTurnText();
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
	window->draw(turntext);
	//Code draw things here
	//this->player.render(this->window);
	this->gameAction->Render();
	

	//--------------------------

	//Render gui
	//window->draw(bar);
	//window->draw(button);
	//window->draw(text);
	//window->draw(guiText);
	//this->RenderGui(this->window);
	this->window->display();


}

void Game::renderButton(sf::RenderTarget* target)
{
	target->draw(this->button1);
}
