#include "Map.h"

void Map::InitMap()
{
	for (int r = -1; r < 900 / 60; r += 1) {
		for (int c = -1; c < 11; c += 1) {
			gridInfo gridInfo;
			gridInfo.id = r * (800 / gridSize) + c;
			gridInfo.row = r;
			gridInfo.column = c;
			gridInfo.buildingID = 0;
			gridInfo.type = "NULL";

			if (c % 2 == 0) {
				gridInfo.grid.setPosition(r * gridSize, c * (gridSize - 10));
			}
			else {
				gridInfo.grid.setPosition(r * gridSize + gridSize / 2, c * (gridSize - 10));
			}

			gridInfo.y = gridInfo.grid.getPosition().y + 30;
			gridInfo.x = gridInfo.grid.getPosition().x + 30;

			gridInfo.grid.scale(0.5f, 0.5f);

			this->gridInfos.push_back(gridInfo);
		}
	}
}

Map::Map()
{
	gridSize = 60.f;
	InitMap();
}

Map::~Map()
{
}

void Map::Render(sf::RenderTarget& target)
{
	sf::Texture texture;

	if (!texture.loadFromFile("Textures/grass_05.png")) {
		std::cout << "Error!";
	}

	for (unsigned int i = 0; i < this->gridInfos.size(); i++) {
		gridInfos[i].grid.setTexture(texture);
		target.draw(gridInfos[i].grid);
	}
}


