#include "Action.h"

Action::Action(sf::RenderWindow* pWindow, sf::Vector2f* pMousePosView)
{
	this->pWindow = pWindow;
	this->pMousePosView = pMousePosView;
}

Action::~Action()
{
	GameEnd();
}

void Action::StartGame(int numPlayer)
{
	this->pMap = new Map(pWindow);

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
					if (pGridPointed != 0) {
						if (gMode == "Move") {
							this->Move();
							this->SetModeToNormal();
						}
						else {
							if (pGridPointed->isUnit && pGridPointed->GetUnit() != 0) {
								this->gMode = "Move";
								this->pGridMoveStart = pGridPointed;
								this->pMap->CreateGridArea(pGridMoveStart,1);
							}
							else {

							}
						}
					}
				}
			}
			// Mouse Right click
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				std::cout << " => End Turn" << std::endl;
				NextTurn();
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
	this->pGridPointed->AddUnit(this->pGridMoveStart->GetUnit());
	this->pMap->UpdatePlayerVision(pGridPointed, 1, this->idPlayerNow);
	this->pGridMoveStart->ClearUnit();
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
	this->SetModeToNormal();
	std::cout << "Turn: " << countTurn;
	std::cout << " ----> Player " << idPlayerNow + 1 << " is playing";
}

void Action::SetModeToNormal()
{
	this->gMode = "Normal";
	this->pGridMoveStart = 0;
	this->pMap->SetGridAllEnable(true);
}

Grid* Action::CheckGridPointed()
{
	std::vector<Grid*> gridHovered;
	for (unsigned int i = 0; i < this->pMap->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->pMap->vGrids[i].size(); j++) {
			if (pMap->vGrids[i][j].isPointed(currentMousePos))
			{
				gridHovered.push_back(&pMap->vGrids[i][j]);
			}
		}
	}
	if (gridHovered.size() > 0) {
		for (unsigned int i = 0; i < gridHovered.size() - 1; i++) {
			bool isTemp = 0;
			for (unsigned int j = 0; j < gridHovered.size() - i - 1; j++) {
				float distanceOne = gridHovered[j]->distanceFromMouse(this->currentMousePos);
				float distanceTwo = gridHovered[j + 1]->distanceFromMouse(this->currentMousePos);
				if (distanceOne > distanceTwo){
					std::swap(gridHovered[j + 1], gridHovered[j]);
					isTemp = 1;
				}
			}
			if (!isTemp) break;
		}
		if(gridHovered[0]->isEnabled()) return gridHovered[0];
	}
	return 0;
}

void Action::Update()
{
	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->CheckGridPointed();

	ClickEvents();
}

void Action::RenderUnit()
{
	for (unsigned int i = 0; i < this->pMap->vUnits.size(); i++) {
		this->pMap->vUnits[i]->Render(this->pWindow);
	}
}

void Action::Render()
{
	if (isWait == false) {
		this->pMap->Render(this->pWindow, this->idPlayerNow);
		this->pMap->ShowGridHighlight(this->pGridPointed, this->gMode);
		this->RenderUnit();
	}
	this->Update();
}