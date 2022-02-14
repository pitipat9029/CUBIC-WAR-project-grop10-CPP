#include "Action.h"

Action::Action(sf::RenderWindow* pWindow, sf::Vector2f* pMousePosView)
{
	this->pWindow = pWindow;
	this->pMousePosView = pMousePosView;
	 this->intitText();
	 this->initFont();
	 this->initBar();
	 this->initButton();
}

Action::~Action()
{
	GameEnd();
}

void Action::StartGame(int numPlayer)
{
	this->pMap = new Map;

	for (int i = 0; i < numPlayer; i++) {
		this->vPlayers.push_back(new Player);
	}
	countTurn = 0;
	RandomStartPosition();
	this->NextTurn();
}

void Action::GameEnd()
{
	for (int i = 0; i < this->vPlayers.size(); i++) {
		delete this->vPlayers[i];
	}
	delete this->pMap;
}

void Action::renderText(sf::RenderTarget *target)
{
	target->draw(this->Playerturn);
}

void Action::Render()
{
	if (isWait == false) {
		this->pMap->Render(this->pWindow);
		ShowGridHighlight();
		this->RenderUnit();
		pWindow->draw(bar);
		pWindow->draw(button);
		pWindow->draw(rollbtn);
		pWindow->draw(pointtext);
		pWindow->draw(endturn);
		pWindow->draw(rolltext);
	}
	else
	{
		this->updateText();
		this->renderText(this->pWindow);
		pWindow->draw(text);
	}
	
	this->Update();
	
	
}

void Action::ClickEvents()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (!this->isMousePress) {
			// Mouse Left click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  
				if (this->isWait) {
					this->isWait = false;
				}
				else {
					if (this->pGridPointed != 0 && !this->isMenuOpen) {
						if (gMode == "Move") {
							this->Move();
						}
						else {
							if (pGridPointed->isUnit && pGridPointed->GetUnit()->isMyUnit(idPlayerNow) && pGridPointed->GetUnit() != 0) {
								this->gMode = "Move";
								this->pGridSelected = pGridPointed;
								this->pMap->CreateGridArea(pGridSelected,1);
							}
							else {
								
							}
						}
					}
				}
				this->isMenuOpen = false;
			}
			//endturn button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
				{	
					std::cout << " => End Turn" << std::endl;
					NextTurn();
				}
			}
			//roll button click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (rollbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
				{
					int ran1 = rand()%6+1;
					int ran2 = rand() % 6 + 1;

					point = point + ran1 + ran2;
					
				}
			}
			// Mouse Right click
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				//std::cout << " => End Turn" << std::endl;
				//NextTurn();
				this->pGridSelected = this->pGridPointed;
				this->isMenuOpen = true;
			}
			
			
			this->isMousePress = true;
		}
	}
	else {
		this->isMousePress = false;
	}
}

void Action::initFont()
{
	this->pGridPointed->AddUnit(this->pGridSelected->GetUnit());
	this->pMap->UpdatePlayerVision(pGridPointed, 1, this->idPlayerNow);
	this->pGridSelected->ClearUnit();
}

void Action::RenderMenu()
{
	//this->pGridPointed->GetCenterPoint();
	float r = 10, grab = 5;
	int x = pGridSelected->vActionButton.size();
	sf::Vector2f centerPos = this->pGridSelected->GetCenterPoint();
	float startX = ((r * x * 2) + (grab * (x - 3))) / 2;
	for (int i = 0; i < x; i++) {
		pGridSelected->vActionButton[i]->SetPosition(sf::Vector2f((centerPos.x - startX) + ((grab+r*2)*i), centerPos.y - 40));
		pGridSelected->vActionButton[i]->Render(this->pWindow);
	}
}

void Action::NextTurn()
{
	this->isWait = true;
	if (this->countTurn == 0) {
		idPlayerNow = 0;
		this->countTurn++;
	}
	else if (this->idPlayerNow < this->vPlayers.size() - 1) {
		this->idPlayerNow++;
	}
	else {
		this->idPlayerNow = 0;
		this->countTurn++;
	}
	
	std::cout << "Turn: " << countTurn;
	std::cout << " ----> Player " << idPlayerNow + 1 << " is playing";
	//pWindow->draw(Playerturn);
}

void Action::intitText()
{
	this->Playerturn.setFont(this->font);
	this->Playerturn.setFillColor(sf::Color::White);
	this->Playerturn.setCharacterSize(32);
	this->Playerturn.setPosition(350.f, 280.f);

	//Click to start text
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(18);
	this->text.setPosition(680.f, 567.f);
	this->text.setString("-> Click to Start ur turn");
	//point text
	this->pointtext.setFont(this->font);
	this->pointtext.setFillColor(sf::Color::White);
	this->pointtext.setCharacterSize(32);
	this->pointtext.setPosition(5.f, 550.f);
	//endtuentext
	this->endturn.setFont(this->font);
	this->endturn.setFillColor(sf::Color::White);
	this->endturn.setCharacterSize(20);
	this->endturn.setPosition(805.f, 560.f);
	endturn.setString("End Turn");

	this->rolltext.setFont(this->font);
	this->rolltext.setFillColor(sf::Color::White);
	this->rolltext.setCharacterSize(20);
	this->rolltext.setPosition(705.f, 560.f);
	rolltext.setString("Roll");
}


void Action::Update()
{


	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->CheckGridPointed();

	//button change color
	if (button.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
	{
		sf::Color lor(128, 128, 128);
		button.setFillColor(lor);
		rollbtn.setFillColor(lor);
	}
	else
	{
		sf::Color col(192, 192, 192);
		button.setFillColor(col);
		rollbtn.setFillColor(col);
	}

	if (rollbtn.getGlobalBounds().contains(sf::Mouse::getPosition(*pWindow).x, sf::Mouse::getPosition(*pWindow).y))
	{
		sf::Color lor(128, 128, 128);
		rollbtn.setFillColor(lor);
	}
	else
	{
		sf::Color col(192, 192, 192);
		rollbtn.setFillColor(col);
	}
	updateText();
	ClickEvents();
}

void Action::Render()
{
	for (unsigned int i = 0; i < this->pMap->vUnits.size(); i++) {
		this->pMap->vUnits[i]->Render(this->pWindow);
	}
}

void Action::Move()
{
	this->pGridPointed->AddUnit(this->pGridMoveStart->GetUnit());
	this->pGridMoveStart->ClearUnit();
	this->pGridMoveStart = 0;
	this->isMoveMode = false;
}
