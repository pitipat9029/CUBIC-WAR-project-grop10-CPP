#include "Action.h"

Action::Action(Map* pMap, sf::RenderWindow* pWindow, std::vector<Grid>& gridInfos,
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

	if (pGridPointed != 0) {
		this->HighlightGrid();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (!this->isMousePress) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					this->pGridPointed->AddUnit("Soldier", pMap->vUnits);
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
		if (gridInfos[i].isHovered(currentMousePos))
		{
			gridHovered.push_back(&gridInfos[i]);
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

void Action::HighlightGrid()
{
	sf::CircleShape rect(35, 6);
	rect.setPosition(pGridPointed->GetPosition().x - 5, pGridPointed->GetPosition().y);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(-1.5f);
	this->pWindow->draw(rect);
}