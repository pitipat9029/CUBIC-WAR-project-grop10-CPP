#include "UImanager.h"

UImanager::UImanager(sf::RenderWindow* pWindow, Action* gameAction)
{
	this->font.loadFromFile("Fonts/gomarice_no_continue.ttf");
	this->pWindow = pWindow;
	this->gameAction = gameAction;
	this->pBtnStart = new MyButton("Start12", sf::Vector2f(450.f, 300.f));
	this->tbgStart.loadFromFile("Textures/bg.jpg");
	this->bgStart.setTexture(tbgStart);
	this->bgStart.scale(600.f / this->tbgStart.getSize().y, 600.f / this->tbgStart.getSize().y);
	this->bgStart.setPosition(0, 0);

	this->tbgWin.loadFromFile("Textures/bg-game-win.jpg");
	this->bgWin.setTexture(tbgWin);
	this->bgWin.scale(600.f / this->tbgWin.getSize().y, 600.f / this->tbgWin.getSize().y);
	this->bgWin.setPosition(0, 0);

	sf::Color col(192, 192, 192);
	//return menu button
	this->returnMenubtn.setFillColor(col);
	this->returnMenubtn.setSize(sf::Vector2f(180.f, 72.f));
	this->returnMenubtn.setOrigin(90.f, 36.f);
	this->returnMenubtn.setPosition(250.f, 370.f);

	this->tReturnMenubtn.setFont(this->font);
	this->tReturnMenubtn.setFillColor(sf::Color::White);
	this->tReturnMenubtn.setCharacterSize(32);
	this->tReturnMenubtn.setString("MAIN MENU");
	sf::FloatRect textRect1 = tReturnMenubtn.getLocalBounds();
	this->tReturnMenubtn.setOrigin(textRect1.left + textRect1.width / 2.0f,
		textRect1.top + textRect1.height / 2.0f);
	this->tReturnMenubtn.setPosition(this->returnMenubtn.getPosition());

	//restart game button
	this->restartbtn.setFillColor(col);
	this->restartbtn.setSize(sf::Vector2f(180.f, 72.f));
	this->restartbtn.setOrigin(90.f, 36.f);
	this->restartbtn.setPosition(250.f, 270.f);

	this->tRestartbtn.setFont(this->font);
	this->tRestartbtn.setFillColor(sf::Color::White);
	this->tRestartbtn.setCharacterSize(32);
	this->tRestartbtn.setString("new game");
	sf::FloatRect textRect4 = tRestartbtn.getLocalBounds();
	this->tRestartbtn.setOrigin(textRect4.left + textRect4.width / 2.0f,
		textRect4.top + textRect4.height / 2.0f);
	this->tRestartbtn.setPosition(this->restartbtn.getPosition());

	this->tPlayerWin.setFont(this->font);
	this->tPlayerWin.setFillColor(sf::Color::Black);
	this->tPlayerWin.setCharacterSize(72);
	this->tPlayerWin.setString("Player 1");
	sf::FloatRect textRect2 = tPlayerWin.getLocalBounds();
	this->tPlayerWin.setOrigin(textRect2.left + textRect2.width / 2.0f,
		textRect2.top + textRect2.height / 2.0f);
	this->tPlayerWin.setPosition(250.f, 120.f);

	this->tWin.setFont(this->font);
	this->tWin.setFillColor(sf::Color(218, 165, 32));
	this->tWin.setCharacterSize(48);
	this->tWin.setString("Win");
	sf::FloatRect textRect3 = tWin.getLocalBounds();
	this->tWin.setOrigin(textRect3.left + textRect3.width / 2.0f,
		textRect3.top + textRect3.height / 2.0f);
	this->tWin.setPosition(250.f, 180.f);
}

UImanager::~UImanager()
{
	delete this->pBtnStart;
}

std::string UImanager::RenderUI(std::string page)
{
	if (page == "start") {
		this->pWindow->draw(this->bgStart);
	}
	else if (page == "result") {
		this->pWindow->draw(this->bgWin);
		this->pWindow->draw(this->restartbtn);
		this->pWindow->draw(this->returnMenubtn);
		this->pWindow->draw(this->tReturnMenubtn);
		this->pWindow->draw(this->tRestartbtn);
		this->pWindow->draw(this->tPlayerWin);
		this->pWindow->draw(this->tWin);
		std::stringstream ss;
		ss << "Player " << this->gameAction->idPlayerNow + 1;
		this->tPlayerWin.setString(ss.str());
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//restart button click
			if (restartbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y)) {
				this->gameAction->StartGame(2);
			}
			//returnmenu button click
			if (returnMenubtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y)) {
				return "super";
			}
		}
	}
	return "";
	//btnStart->Render(this->pWindow);
}
