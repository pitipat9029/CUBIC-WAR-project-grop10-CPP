#include "Map.h"

void Map::InitMap()
{
	for (int r = -1; r < this->maxRow; r += 1) {
		for (int c = -1; c < this->maxColumn; c += 1) {
			Grid grid(r, c, this->gridSize);
			if (!((c < 0 || (c > this->maxColumn - 2 && (r % 2) != 0)) || (r < 0 || r >= this->maxRow))) {
				grid.SetEnabled(true);
			} else {
				grid.SetEnabled(false);
			}
			this->vGrids.push_back(grid);
		}
	}
}

Map::Map()
{
	gridSize.x = 60.f;
	gridSize.y = 70.f;

	maxRow = 11;
	maxColumn = (900 / gridSize.x);

	InitMap();
}

Map::~Map()
{
}

void Map::Render(sf::RenderTarget* target)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		vGrids[i].Render(target);
	}
	for (unsigned int i = 0; i < this->vUnits.size(); i++) {
		vUnits[i].Render(target);
	}
}


