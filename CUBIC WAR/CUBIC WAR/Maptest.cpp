#include "Maptest.h"

void Maptest::InitMap()
{
	this->grid.scale(1.35f, 1.35f);

	for (int r = 0; r < 800 / gridSize; r += 1) {
		for (int c = 0; c < 600 / gridSize; c += 1) {
			
			this->grid.setPosition(r* gridSize, c* gridSize);
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
	sf::Texture texture;

	if (!texture.loadFromFile("Textures/grass.png")) {
		std::cout << "Error!";
	}

	texture.setSmooth(true);
	texture.setSmooth(true);

	for (unsigned int i = 0; i < grids.size(); i++) {
		grids[i].setTexture(texture);
		target.draw(grids[i]);
	}
}


