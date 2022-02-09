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
	this->pMap = new Map;

	for (int i = 0; i < numPlayer; i++) {
		this->gamePlayers.push_back(new Player);
	}
	playerNow = 0;
}

void Action::GameEnd()
{
	for (int i = 0; i < this->gamePlayers.size(); i++) {
		delete this->gamePlayers[i];
	}
	delete this->pMap;
}


void Action::Render()
{
	this->pMap->Render(this->pWindow);

	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->CheckGridPointed();

	ShowGridHighlight();
	ClickEvents();
}

void Action::ClickEvents()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (!this->isMousePress) {
			// Mouse Left click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (pGridPointed != 0) {
					if (this->isMoveMode) {
						this->Move();
						this->pMap->SetAllGridEnable(true);
						this->isMoveMode = false;
					}
					else {
						if (pGridPointed->isUnit && pGridPointed->GetUnit() != 0) {
							this->pGridMoveStart = pGridPointed;
							this->isMoveMode = true;
						}
						else {
							this->pGridPointed->AddUnit("Soldier", pMap->vUnits);
						}
					}
				}
			}
			// Mouse Right click
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				if (pGridPointed != 0) {
					this->pGridPointed->CreateBuilding("B");
				}
			}
			this->isMousePress = true;
		}
	}
	else {
		this->isMousePress = false;
	}
}

void Action::Update()
{
}

Grid* Action::CheckGridPointed()
{
	std::vector<Grid*> gridHovered;
	for (unsigned int i = 0; i < this->pMap->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->pMap->vGrids[i].size(); j++) {
			if (pMap->vGrids[i][j].isHovered(currentMousePos))
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

void Action::HighlightGridPointed(sf::Color cFill, sf::Color cOutline)
{
	sf::CircleShape rect(35, 6);
	rect.setPosition(pGridPointed->GetPosition().x - 5, pGridPointed->GetPosition().y);
	rect.setFillColor(cFill);
	rect.setOutlineColor(cOutline);
	rect.setOutlineThickness(-1.5f);
	this->pWindow->draw(rect);
}

void Action::HighlightGrids(int radius, sf::Color cFill, sf::Color cOutline)
{
	this->pMap->SetAllGridEnable(false);
	sf::CircleShape rect(35, 6);
	rect.setFillColor(cFill);
	for (int q = this->pGridMoveStart->GetRC().y - radius; q <= this->pGridMoveStart->GetRC().y + radius; q++) {
		for (int r = this->pGridMoveStart->GetRC().x - radius; r <= this->pGridMoveStart->GetRC().x + radius; r++) {
			if (abs( - (q - this->pGridMoveStart->GetRC().y) - (r - this->pGridMoveStart->GetRC().x)) <= radius) {
				int col = q + (r - (r & 1)) / 2;
				int row = r;
				if (&this->pMap->vGrids[row + 1][col + 1] != this->pGridMoveStart) {
					this->pMap->vGrids[row + 1][col + 1].SetEnabled(true);
					rect.setPosition(this->pMap->vGrids[row + 1][col + 1].GetPosition().x - 5, this->pMap->vGrids[row + 1][col + 1].GetPosition().y);
					this->pWindow->draw(rect);
				}
			}
		}
	}
}

void Action::ShowGridHighlight()
{
	if (this->isMoveMode) {
		this->HighlightGrids(1, sf::Color(0, 255, 0, 100), sf::Color(0, 0, 0, 0));
		if (this->pGridPointed != 0) this->HighlightGridPointed(sf::Color(0, 255, 0, 100), sf::Color(0, 0, 0, 0));
	}
	else {
		if (this->pGridPointed != 0) this->HighlightGridPointed(sf::Color(0, 0, 0, 0), sf::Color::White);
	}
}

void Action::Move()
{
	this->pGridPointed->AddUnit(this->pGridMoveStart->GetUnit());
	this->pGridMoveStart->ClearUnit();
	this->pGridMoveStart = 0;
}
