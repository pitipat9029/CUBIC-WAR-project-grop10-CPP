#include "Building.h"

Building::Building()
{
	//gridSize = 50.f;
}

Building::~Building()
{

}

void Building::Render()
{
	
}

void Building::Create(std::vector<Maptest::gridInfo> grids, sf::Vector2f MP, sf::RenderTarget& window)
{
	double xPos, yPos;
	for (unsigned int i = 0; i < grids.size() - 1; i++) {
		bool isTemp = 0;
		for (unsigned int j = 0; j < grids.size() - i - 1; j++) {
		
			if (abs(grids[j].x - MP.x) > abs(grids[j + 1].x - MP.x)) {
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

			if (abs(grids[j].y - MP.y) > abs(grids[j + 1].y - MP.y)) {
				std::swap(grids[j + 1], grids[j]);
				isTemp = 1;
			}
		}
		if (!isTemp) break;
	}
	yPos = grids[0].y;

	sf::RectangleShape rect;
	rect.setPosition(xPos-25.5, yPos-25.5);
	rect.setSize(sf::Vector2f(50.f,50.f));
	rect.setFillColor(sf::Color::Green);
	window.draw(rect);
}
