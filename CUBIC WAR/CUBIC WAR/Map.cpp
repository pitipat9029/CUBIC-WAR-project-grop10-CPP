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
	std::cout << "Map was create" << std::endl;

	// Set map properties
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
	std::cout << "Map was delect" << std::endl;
}

void Map::Render(sf::RenderTarget* target)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			vGrids[i][j].Render(target);
		}
	}
}

void Map::SetGridAllEnable(bool b)
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if (!((j <= 0 || (j > this->maxColumn-1 && (i % 2) == 0)) || (i <= 0 || i >= this->maxRow+1))) {
				vGrids[i][j].SetEnabled(b);
			}
		}
	}
}

void Map::SetGridEdgeDisable()
{
	for (unsigned int i = 0; i < this->vGrids.size(); i++) {
		for (unsigned int j = 0; j < this->vGrids[i].size(); j++) {
			if ((j <= 0 || (j > this->maxColumn - 1 && (i % 2) == 0)) || (i <= 0 || i >= this->maxRow + 1)) {
				vGrids[i][j].SetEnabled(false);
			}
		}
	}
}


