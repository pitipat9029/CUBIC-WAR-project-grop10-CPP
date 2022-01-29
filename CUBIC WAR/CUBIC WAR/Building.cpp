#include "Building.h"

Building::Building(Maptest* map, sf::RenderTarget* window, std::vector<Maptest::gridInfo>& gridInfos, sf::Vector2f* mousePosView) : gridInfos(gridInfos)
{
	this->isCreatdMode = 1;
	this->map = map;
	this->window = window;
	this->mousePosView = mousePosView;
}

/*Building::Building()
{
	this->isCreatdMode = 0;
	this->map = NULL;
	this->window = NULL;
	this->mousePosView = NULL;
}*/

Building::~Building()
{
}

void Building::Update(std::vector<sPlayerBuilding>& playerBuildings)
{
	if (this->isCreatdMode) {
		this->Create(this->gridInfos, playerBuildings);
	}
	Render(playerBuildings);
}

void Building::Render(std::vector<sPlayerBuilding>& playerBuildings)
{
	for (unsigned int i = 0; i < playerBuildings.size(); i++) {
		window->draw(playerBuildings[i].object);
	}
}

void Building::Create(std::vector<Maptest::gridInfo> grids, std::vector<sPlayerBuilding>& playerBuildings)
{
	float xPos, yPos;
	for (unsigned int i = 0; i < grids.size() - 1; i++) {
		bool isTemp = 0;
		for (unsigned int j = 0; j < grids.size() - i - 1; j++) {
		
			if (abs(grids[j].x - mousePosView->x) > abs(grids[j + 1].x - mousePosView->x)) {
				std::swap(grids[j+1], grids[j]);
				isTemp = 1;
			}
		}
		if (!isTemp) break;
	}
	xPos = grids[0].x;

	for (unsigned int i = 0; i < grids.size() - 1; i++) {
		bool isTemp = 0;
		for (unsigned int j = 0; j < grids.size() - i - 1; j++) {

			if (abs(grids[j].y - mousePosView->y) > abs(grids[j + 1].y - mousePosView->y)) {
				std::swap(grids[j + 1], grids[j]);
				isTemp = 1;
			}
		}
		if (!isTemp) break;
	}
	yPos = grids[0].y;

	sf::RectangleShape rect;
	rect.setPosition(xPos-25, yPos-25);
	rect.setSize(sf::Vector2f(50.f,50.f));
	rect.setFillColor(sf::Color(0, 255, 0, 100));
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(-2.f);
	window->draw(rect);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		this->isCreatdMode = 0;

		sPlayerBuilding newBuilding;

		newBuilding.object.setOrigin(25.f, 25.f);
		newBuilding.object.setPosition(xPos, yPos);
		newBuilding.object.setSize(sf::Vector2f(50.f, 50.f));
		newBuilding.object.setFillColor(sf::Color::Red);

		playerBuildings.push_back(newBuilding);
	}
}
