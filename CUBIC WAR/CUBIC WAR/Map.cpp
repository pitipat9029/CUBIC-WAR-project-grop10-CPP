#include "Map.h"

void Map::InitMap()
{
	std::vector<Grid> gridRow;
	for (int r = -1; r < this->maxRow; r += 1) {
		gridRow.clear();
		for (int c = -1; c < this->maxColumn; c += 1) {
			Grid grid(r, c, this->gridSize);
			if (!((c < 0 || (c > this->maxColumn - 2 && (r % 2) != 0)) || (r < 0 || r >= this->maxRow))) {
				grid.SetEnabled(true);
			} else {
				grid.SetEnabled(false);
			}
			gridRow.push_back(grid);
		}
		this->vGrids.push_back(gridRow);
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
	for (unsigned int i = 0; i < this->vUnits.size(); i++) {
		delete this->vUnits[i];
	}
}

void Map::Render(sf::RenderTarget* target)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			vGrids[i][j].Render(target);
		}
	}
	for (unsigned int i = 0; i < this->vUnits.size(); i++) {
		vUnits[i]->Render(target);
	}
}

void Map::SetAllGridEnable(bool b)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (!((j < 0 || (j > this->maxColumn - 2 && (i % 2) != 0)) || (i < 0 || i >= this->maxRow))) {
				vGrids[i][j].SetEnabled(b);
			}
		}
	}
}


