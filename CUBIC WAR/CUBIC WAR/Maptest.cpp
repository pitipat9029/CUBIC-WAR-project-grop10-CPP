#include "Maptest.h"

void Maptest::InitMap()
{
	for (int r = 0; r < 800 / gridSize; r += 1) {
		for (int c = 0; c < 600 / gridSize; c += 1) {
			this->grid.setSize(sf::Vector2f(this->gridSize, this->gridSize));
			this->grid.setPosition(r* gridSize, c* gridSize);
			this->grid.setOutlineThickness(1);
			this->grid.setOutlineColor(sf::Color::Black);
			this->grid.setFillColor(sf::Color::White);
			this->grids.push_back(this->grid);

			gridInfo gridInfo;
			gridInfo.id = r * (800 / gridSize) + c;
			gridInfo.buildingID = 0;
			gridInfo.type = "NULL";
			gridInfo.x = grid.getPosition().x + (gridSize / 2);
			gridInfo.y = grid.getPosition().y + (gridSize / 2);
			this->gridInfos.push_back(gridInfo);
		}
	}
}

Maptest::Maptest()
{
	gridSize = 50.f;
	InitMap();
}

Maptest::~Maptest()
{
}

void Maptest::Render(sf::RenderTarget& target)
{
	for (unsigned int i = 0; i < grids.size(); i++) {
		target.draw(grids[i]);
	}
}


