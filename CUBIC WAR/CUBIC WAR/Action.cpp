#include "Action.h"

Action::Action(Map* pMap, sf::RenderWindow* pWindow, std::vector<std::vector<Grid>>& gridInfos,
	std::vector<Player>& gamePlayers, sf::Vector2f* pMousePosView) : gridInfos(gridInfos), gamePlayers(gamePlayers)
{
	this->isCreatdMode = 1;
	this->pMap = pMap;
	this->pWindow = pWindow;
	this->pMousePosView = pMousePosView;
}

Action::~Action()
{
}

void Action::Update()
{
	this->currentMousePos = sf::Mouse::getPosition(*this->pWindow);
	this->pGridPointed = this->CheckGridPointed();

	if (pGridMoveStart != 0) {
		this->HighlightGrids(1, sf::Color(0, 255, 0, 100), sf::Color(0, 0, 0, 0));
	}
	if (pGridPointed != 0) {
		if (pGridMoveStart != 0) {
			this->HighlightGrid(sf::Color(0, 255, 0, 100), sf::Color(0, 0, 0, 0));
		}
		else {
			this->HighlightGrid(sf::Color(0, 0, 0, 0), sf::Color::White);
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (!this->isMousePress) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (pGridMoveStart != 0) {
						this->Move();
						this->pMap->SetAllGridEnable(true);
						for (int i = 0; i < this->pMap->vUnits.size(); i++) {
							std::cout << this->pMap->vUnits[i] << std::endl;
						}
						std::cout << "---------------------" << std::endl;
					}else{
						if (pGridPointed->isUnit && pGridPointed->GetUnit() != 0) {
							this->pGridMoveStart = pGridPointed;
						}
						else {
							this->pGridPointed->AddUnit("Soldier", pMap->vUnits);
						}
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					this->pGridPointed->CreateBuilding("B");
				}
				this->isMousePress = true;
			}
		}
		else {
			this->isMousePress = false;
		}
	}
}

Grid* Action::CheckGridPointed()
{
	std::vector<Grid*> gridHovered;
	for (unsigned int i = 0; i < this->gridInfos.size(); i++) {
		for (unsigned int j = 0; j < this->gridInfos[i].size(); j++) {
			if (gridInfos[i][j].isHovered(currentMousePos))
			{
				gridHovered.push_back(&gridInfos[i][j]);
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

void Action::HighlightGrid(sf::Color cFill, sf::Color cOutline)
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
	sf::CircleShape rect(35, 6);
	rect.setFillColor(cFill);
	this->pMap->SetAllGridEnable(false);
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

void Action::Move()
{
	this->pGridPointed->AddUnit(this->pGridMoveStart->GetUnit());
	this->pGridMoveStart->ClearUnit();
	this->pGridMoveStart = 0;
}
