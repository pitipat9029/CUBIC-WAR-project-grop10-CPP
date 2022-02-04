#include "Map.h"

void Map::InitMap()
{
	for (int c = -1; c < 11; c += 1) {
		for (int r = -1; r < 900 / 60; r += 1) {
			Building grid;
			grid.id = r * (800 / gridSize) + c;
			grid.row = r;
			grid.column = c;

			if (c % 2 == 0) {
				grid.grid.setPosition(r * gridSize, c * (gridSize - 10));
			}
			else {
				grid.grid.setPosition(r * gridSize + gridSize / 2, c * (gridSize - 10));
			}

			grid.yPos = grid.grid.getPosition().y + 30;
			grid.xPos = grid.grid.getPosition().x + 30;

			grid.grid.scale(0.5f, 0.5f);

			this->grids.push_back(grid);
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

void Map::Render(sf::RenderTarget* target)
{
	for (unsigned int i = 0; i < this->grids.size(); i++) {
		grids[i].Render(target);
	}
}


