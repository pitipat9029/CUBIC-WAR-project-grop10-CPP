#include "UImanager.h"

UImanager::UImanager(sf::RenderWindow* pWindow)
{
	this->pWindow = pWindow;
	this->pBtnStart = new MyButton("Start12", sf::Vector2f(450.f, 300.f));
	this->tbgStart.loadFromFile("Textures/bg.jpg");
	this->bgStart.setTexture(tbgStart);
	this->bgStart.scale(600.f / this->tbgStart.getSize().y, 600.f / this->tbgStart.getSize().y);
	this->bgStart.setPosition(0, 0);
}

UImanager::~UImanager()
{
	delete this->pBtnStart;
}

void UImanager::RenderUI(std::string page)
{
	if (page == "start") {
		this->pWindow->draw(this->bgStart);
	}
	//btnStart->Render(this->pWindow);
}
