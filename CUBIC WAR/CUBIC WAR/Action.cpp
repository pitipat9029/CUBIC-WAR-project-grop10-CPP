#include "Action.h"

Action::Action(Map* map, sf::RenderWindow* window, std::vector<Map::gridInfo>& gridInfos,
	std::vector<Player>& gamePlayers, sf::Vector2f* mousePosView) : gridInfos(gridInfos), gamePlayers(gamePlayers)
{
	this->isCreatdMode = 1;
	this->map = map;
	this->window = window;
	this->mousePosView = mousePosView;
}

Action::~Action()
{
}

void Action::Update()
{
	if (this->isCreatdMode) {
		this->Create();
	}
	Render();
}

void Action::Render()
{
	for (unsigned int i = 0; i < this->gamePlayers[0].myBuildings.size(); i++) {
		window->draw(this->gamePlayers[0].myBuildings[i].object);
	}
}

void Action::AddBuilding(int type, float xPos, float yPos)
{
	Building newBuilding(type);

	newBuilding.object.setOrigin(25.f, 25.f);
	newBuilding.object.setPosition(xPos, yPos);
	newBuilding.object.setSize(sf::Vector2f(50.f, 50.f));
	newBuilding.object.setFillColor(sf::Color::Red);

	this->gamePlayers[0].myBuildings.push_back(newBuilding);
}

void Action::Create()
{
	float xPos = 35, yPos = 30;
	std::vector<Map::gridInfo> gridHover;
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(*this->window);
	for (unsigned int i = 0; i < this->gridInfos.size(); i++) {
		if (gridInfos[i].grid.getGlobalBounds().contains(currentMousePos.x, currentMousePos.y))
		{
			gridHover.push_back(gridInfos[i]);
		}
	}
	if (gridHover.size() > 0) {

		for (unsigned int i = 0; i < gridHover.size() - 1; i++) {
			bool isTemp = 0;
			for (unsigned int j = 0; j < gridHover.size() - i - 1; j++) {
				float distanceOne = sqrt(pow(gridHover[j].y - mousePosView->y, 2) + pow(gridHover[j].x - mousePosView->x, 2));
				float distanceTwo = sqrt(pow(gridHover[j + 1].y - mousePosView->y, 2) + pow(gridHover[j + 1].x - mousePosView->x, 2));
				if (distanceOne > distanceTwo){
					std::swap(gridHover[j + 1], gridHover[j]);
					isTemp = 1;
				}
			}
			if (!isTemp) break;
		}
	
		yPos = gridHover[0].y;
		xPos = gridHover[0].x;
		if (!((gridHover[0].row < 0 || (gridHover[0].row >= 14 && (gridHover[0].column % 2) != 0))
			|| (gridHover[0].column < 0 || gridHover[0].column >= 11))) {

			sf::CircleShape rect(35, 6);
			rect.setPosition(xPos - 35, yPos - 30);
			rect.setFillColor(sf::Color(0, 255, 0, 100));
			rect.setOutlineColor(sf::Color::Green);
			rect.setOutlineThickness(-2.f);
			window->draw(rect);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(*this->window);
		if ((currentMousePos.x >= 0 && currentMousePos.x <= 600) && (currentMousePos.y >= 0 && currentMousePos.y <= 800))
		{
			this->isCreatdMode = 0;
			AddBuilding(0,xPos,yPos);
		}
	}
}