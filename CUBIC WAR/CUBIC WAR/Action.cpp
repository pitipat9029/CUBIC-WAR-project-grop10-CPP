#include "Action.h"

Action::Action(Map* pMap, sf::RenderWindow* pWindow, std::vector<Building>& gridInfos,
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
	this->MousePointer();
}

void Action::MousePointer()
{
	float xPos = 35, yPos = 30;
	std::vector<Building *> gridHover;
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(*this->pWindow);

	for (unsigned int i = 0; i < this->gridInfos.size(); i++) {
		if (gridInfos[i].grid.getGlobalBounds().contains(currentMousePos.x, currentMousePos.y))
		{
			gridHover.push_back(&gridInfos[i]);
		}
	}

	if (gridHover.size() > 0) {

		for (unsigned int i = 0; i < gridHover.size() - 1; i++) {
			bool isTemp = 0;
			for (unsigned int j = 0; j < gridHover.size() - i - 1; j++) {
				float distanceOne = sqrt(pow(gridHover[j]->yPos - currentMousePos.y, 2) + pow(gridHover[j]->xPos - currentMousePos.x, 2));
				float distanceTwo = sqrt(pow(gridHover[j + 1]->yPos - currentMousePos.y, 2) + pow(gridHover[j + 1]->xPos - currentMousePos.x, 2));
				if (distanceOne > distanceTwo){
					std::swap(gridHover[j + 1], gridHover[j]);
					isTemp = 1;
				}
			}
			if (!isTemp) break;
		}
	
		yPos = gridHover[0]->yPos;
		xPos = gridHover[0]->xPos;
		if (!((gridHover[0]->row < 0 || (gridHover[0]->row >= 14 && (gridHover[0]->column % 2) != 0))
			|| (gridHover[0]->column < 0 || gridHover[0]->column >= 11))) {


			sf::CircleShape rect(35, 6);
			rect.setPosition(xPos - 35, yPos - 30);
			rect.setFillColor(sf::Color(0, 0, 0, 0));
			rect.setOutlineColor(sf::Color::White);
			rect.setOutlineThickness(-1.5f);
			pWindow->draw(rect);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (!this->isMousePress) {
					gridHover[0]->CreateBuilding("B");
					isMousePress = true;
				}
			}else{
				isMousePress = false;
			}
		}
	}
}