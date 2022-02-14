#include "Action.h"

Action::Action(sf::RenderWindow* pWindow)
{
	this->pWindow = pWindow;
}

Action::~Action()
{
	GameEnd();
}

void Action::StartGame(int numPlayer)
{
	this->pMap = new Map(this->pWindow, &this->currentMousePos, &this->idPlayerNow);

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

void Action::RandomStartPosition()
{
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[5][3].CreateBuilding("B", 0), 1,0);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[6][3].AddUnit("Engineer", this->pMap->vUnits, 0), 1, 0);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[8][12].CreateBuilding("B", 1), 1, 1);
	this->pMap->UpdatePlayerVision(this->pMap->vGrids[7][13].AddUnit("Engineer", this->pMap->vUnits, 1), 1, 1);
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
							this->SetToNormalMode();
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

void Action::Move()
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
	this->SetToNormalMode();
	std::cout << "Turn: " << countTurn;
	std::cout << " ----> Player " << idPlayerNow + 1 << " is playing";
}

void Action::SetToNormalMode()
{
	this->gMode = "Normal";
	this->pGridSelected = 0;
	this->pMap->SetGridAllEnable(true);
}

void Action::Update()
{
	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->pMap->UpdatePointedGrid();
	ClickEvents();
}

void Action::Render()
{
	if (isWait == false) {
		this->pMap->RenderMap();
		this->pMap->ShowGridHighlight(this->gMode);
		this->pMap->RenderUnits();
		if (isMenuOpen) {
			this->RenderMenu();
		}
	}
	this->Update();
}