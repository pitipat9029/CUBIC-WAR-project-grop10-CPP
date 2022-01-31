#include "Action.h"

Action::Action(Map* map, sf::RenderWindow* window, std::vector<Map::gridInfo>& gridInfos, std::vector<Player>& gamePlayers, sf::Vector2f* mousePosView) : gridInfos(gridInfos), gamePlayers(gamePlayers)
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
	Building newBuilding;

	newBuilding.object.setOrigin(25.f, 25.f);
	newBuilding.object.setPosition(xPos, yPos);
	newBuilding.object.setSize(sf::Vector2f(50.f, 50.f));
	newBuilding.object.setFillColor(sf::Color::Red);

	this->gamePlayers[0].myBuildings.push_back(newBuilding);
}

void Action::Create()
{
	float xPos, yPos;
	for (unsigned int i = 0; i < this->gridInfos.size() - 1; i++) {
		bool isTemp = 0;
		for (unsigned int j = 0; j < this->gridInfos.size() - i - 1; j++) {

			if (abs(this->gridInfos[j].x - mousePosView->x) > abs(this->gridInfos[j + 1].x - mousePosView->x)) {
				std::swap(this->gridInfos[j + 1], this->gridInfos[j]);
				isTemp = 1;
			}
		}
		if (!isTemp) break;
	}
	xPos = this->gridInfos[0].x;

	for (unsigned int i = 0; i < this->gridInfos.size() - 1; i++) {
		bool isTemp = 0;
		for (unsigned int j = 0; j < this->gridInfos.size() - i - 1; j++) {

			if (abs(this->gridInfos[j].y - mousePosView->y) > abs(this->gridInfos[j + 1].y - mousePosView->y)) {
				std::swap(this->gridInfos[j + 1], this->gridInfos[j]);
				isTemp = 1;
			}
		}
		if (!isTemp) break;
	}
	yPos = this->gridInfos[0].y;

	sf::RectangleShape rect;
	rect.setPosition(xPos - 25, yPos - 25);
	rect.setSize(sf::Vector2f(50.f, 50.f));
	rect.setFillColor(sf::Color(0, 255, 0, 100));
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(-2.f);
	window->draw(rect);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(*this->window);
		if ((currentMousePos.x >= 0 && currentMousePos.x <= 600) && (currentMousePos.y >= 0 && currentMousePos.y <= 800))
		{
			this->isCreatdMode = 0;

			Building newBuilding;

			newBuilding.object.setOrigin(25.f, 25.f);
			newBuilding.object.setPosition(xPos, yPos);
			newBuilding.object.setSize(sf::Vector2f(50.f, 50.f));
			newBuilding.object.setFillColor(sf::Color::Red);

			this->gamePlayers[0].myBuildings.push_back(newBuilding);
		}
	}
}